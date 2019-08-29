#include <Servo.h>
#include <Dabble.h>
#define PI 3.1425926
#define MAXVAL 10
#define WHEELSINCAR 4
bool calibrate = false; //set all servos to 90 for calibration
bool pythonflag = false;
int calibrateVal = 90; //inital servo value
//Servo servo1, servo2, servo3, servo4;
int blueToothVal;
int controlVal = 0;
int motorVal;

char lastValue;
int i = 0;
int taster = 5;
int led = 7;
int messdaten = 6;
int abfrage = 0;
int zaehler = 0;
int counter = 0;
//blutetooth app values

int pos = 0;
int dir = 0;
int  v = 0;
float servopos = 90;
float servodir = 0;
float servostep = 0.05;
int limit = 2048;
float vstep = 10;

int mPWM[WHEELSINCAR];
int mV[WHEELSINCAR];
int mR[WHEELSINCAR];
int servoPin[WHEELSINCAR];
Servo servo[WHEELSINCAR];


float dx = 1;
float dy = 1;
float x []  = {-dx, -dx};
float y []  = {dy, -dy};
float wheel_x[WHEELSINCAR];
float wheel_y[WHEELSINCAR];
float angle[WHEELSINCAR];
float wheelspeed[WHEELSINCAR];
float milad[3];

bool on = false;
typedef unsigned char uchar;

// Dieser Code ist fabelhaft.
float bytesToFloat(uchar b0, uchar b1, uchar b2, uchar b3) {
  float output;
  *((uchar*)(&output) + 3) = b0;
  *((uchar*)(&output) + 2) = b1;
  *((uchar*)(&output) + 1) = b2;
  *((uchar*)(&output) + 0) = b3;
  return output;
}
void setup() {

  Serial.begin(9600);
  Dabble.begin(38400);
  pinMode(taster, INPUT);
  pinMode(led, OUTPUT);
  pinMode(messdaten, OUTPUT);
  //  pinMode(links, OUTPUT);

  //pinbelegung
  for (int i = 0; i < WHEELSINCAR; i++) {
    servoPin[i] = 3 * i + 3;
    servo[i].attach(servoPin[i]);

    servo[i].write(calibrateVal);
    mPWM[i] = 3 * i + 4;
    pinMode(mPWM[i], OUTPUT);
    mV[i] = 22 + 2 * i;
    pinMode(mV[i], OUTPUT);
    mR[i] = 23 + 2 * i;
    pinMode(mR[i], OUTPUT);

    //quick fix
    pinMode(44 + i, OUTPUT);
    digitalWrite(44 + i, HIGH);
  }
}

void loop() {

  //servo[1].write(180);
  Dabble.processInput();

  if (Serial.available()) {
    blueToothVal = Serial.read();
    // Handy Fernsteuerung
    if (blueToothVal == 255) {
      for (int counter = 0; counter < 7; counter++) {
        while (!Serial.available());
        blueToothVal = Serial.read();
        Serial.println(blueToothVal);
        if (counter == 4)
          switch (blueToothVal) {
            case 2:
              v = 0;
              break;
            case 1:
              servopos = calibrateVal;
          }
        if (counter == 5) {
          switch (blueToothVal)
          {
            case 4://links
              //digitalWrite(messdaten, HIGH);
              //for (int i = 0; i < WHEELSINCAR; i++)
              //servo[i].write(pos = (pos > 180 ? 180 : pos + 20));
              servodir = servostep;
              //servo[0].write(0);
              break;
            case 8://rechts
              //digitalWrite(messdaten, HIGH)
              // for (int i = 0; i < WHEELSINCAR; i++)
              // servo[i].write(pos = (pos < -120 ? 120 : pos - 20));
              servodir = -servostep;
              //servo[0].write(40);
              //
              //Serial.println("*");
              break;
            case 1://oben
              // on = 1;
              dir = 1;

              break;
            case 2://unten
              //on = 0;
              dir = -1;
              //analogWrite(mPWM[0], 255);
              break;
            case 0://aus
              //digitalWrite(messdaten, LOW);
              //analogWrite(mPWM[0], 0);
              dir = servodir = 0;
              //servo1.write(-120);
          }
        }
      }
    }

    // Dieser Code ist einzigartig.
    if (blueToothVal == 254) {
      pythonflag = true;
      byte f[4];
      for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 4; i++) {
          while (!Serial.available());
          f[i] = Serial.read();
        }
        milad[j] = bytesToFloat(f[3], f[2], f[1], f[0]);
      }
      //milad0: y milad1: x milad2: w


      /*
         Code muss hier allgemein gehalten werden, da Betrag und Phase sich fortlaufend ändern werden.
      */
      for (int i = 0; i < WHEELSINCAR; i++)
      {
        Serial.println(i);
        wheel_x[i] = milad[1] + milad[2]  * y[i % 2];
        Serial.println(wheel_x[i]);
        wheel_y[i] = milad[0] + milad[2]  * x[i / 2];
        Serial.println(wheel_y[i]);
        angle[i] = atan2( wheel_y[i], wheel_x[i]) * 180 / PI+90;
        if (angle[i]>180) angle[i]-=360;
       /* if (i % 2)
          angle[i] += 90;
        else
          angle[i] -= 90;*/
        //Serial.println(angle[i]);
        on = angle[i] < 0;
        angle[i] = (on ? angle[i] + 180 : angle[i]);
        wheelspeed[i] = sqrt((wheel_x[i] * wheel_x[i]) + (wheel_y[i] * wheel_y[i]));

        digitalWrite(mV[i], on);
        digitalWrite(mR[i], !on);
        analogWrite(mPWM[i], min(wheelspeed[i] * 255 / MAXVAL, 255));
        servo[i].write(angle[i] * 1.05);
      }
    }

  }
  if (!pythonflag) {
    v += vstep * dir;
    v = min(v, limit);
    v = max(v, -limit);
    v = (v > 0 ? v - 1 : v + 1);
    on = v > 0;
    for (int i = 0; i < WHEELSINCAR ; i++) {
      digitalWrite(mV[i], on);  // Motor beginnt zu rotieren
      digitalWrite(mR[i], !on);
      analogWrite(mPWM[i], abs( v) / 8);
    }
    servopos += servodir;
    servopos = max(0, servopos);
    servopos = min(170, servopos);

    for (int i = 0; i < WHEELSINCAR ; i++)
      servo[i].write(servopos);
    //Serial.println(servopos);
    if (controlVal == '2') {
      Serial.write("Messdaten anfordern\n");
      digitalWrite(messdaten, HIGH);
      delay (500);
      digitalWrite(messdaten, LOW);
      Serial.write("...\n");
      Serial.write("Messdaten gesendet\n");
      controlVal = 0;
      //}te("...\n");
      Serial.write("Messdaten gesendet\n");
      controlVal = 0;
    }
  }

}

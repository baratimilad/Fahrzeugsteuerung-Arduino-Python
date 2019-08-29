#include <Servo.h>
#include <Dabble.h>
#define PI 3.1425926
#define MAXVAL 10


Servo servo1, servo2, servo3, servo4;
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
int hoch = 44;
int links = 46;
int unten = 48;
int rechts = 50;

int pos = 0;

int M1v = 22;
int M1r = 23;
int M1PWM = 4;
int servoPin1 = 3;

int M2v = 24;
int M2r = 25;
int M2PWM = 7;
int servoPin2 = 6;
/*
  int M3v = 22;
  int M3r = 23;
  int M3PWM = 4;
  int servoPin3 = 3;

  int M4v = 22;
  int M4r = 23;
  int M4PWM = 4;
  int servoPin4 = 3;
*/
int on = 0;
float milad[4];

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

int d_x = 1;
int d_y = 1;
float wheel_x;
float wheel_y;
float angle;
float abs_v;

void setup() {
  Serial.begin(9600);
//  Serial1.begin(9600);
  //  Serial2.begin(9600);
  //Serial3.begin(9600);
  Dabble.begin(38400);
  servo1.attach(servoPin1);
    servo2.attach(servoPin2);
   /* servo3.attach(servoPin3);
    servo4.attach(servoPin4);
    //servo1.write(0);
    //servo2.write(0);
    pinMode(taster, INPUT);
    pinMode(led, OUTPUT);
    pinMode(messdaten, OUTPUT);
    pinMode(links, OUTPUT);
  */
  pinMode(M1v, OUTPUT);
  pinMode(M1r, OUTPUT);
  pinMode(M1PWM, OUTPUT);
  /*
    pinMode(M2v, OUTPUT);
    pinMode(M2r, OUTPUT);
    //pinMode(M2PWM, OUTPUT);

    pinMode(M3v, OUTPUT);
    pinMode(M3r, OUTPUT);
    //pinMode(M3PWM, OUTPUT);

    pinMode(M4v, OUTPUT);
    pinMode(M4r, OUTPUT);
    //pinMode(M4PWM, OUTPUT);
  */
}

void loop() {

  Dabble.processInput();




  if (Serial.available())
  {
    blueToothVal = Serial.read();
    if (blueToothVal == 255) {
      counter = 0;
    }
    counter++;

    // Dieser Code ist einzigartig.
    if (blueToothVal == 254) {
      byte f[4];
      for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 4; i++) {
          while (!Serial.available());
          f[i] = Serial.read();
        }
        milad[j] = bytesToFloat(f[3], f[2], f[1], f[0]);
        Serial.println(milad[j]);
      }
      wheel_x = milad[1] - 0 * d_y;
      wheel_y = milad[0] + 0 * d_x;

      angle = atan2(wheel_x, wheel_y) * 180 / PI;
      bool on = angle < 0;
      angle = (angle < 0 ? angle + 180 : angle);
      abs_v = sqrt((wheel_x * wheel_x) + (wheel_y * wheel_y));


      // Serial.println(angle);
      //Serial.println(abs_v);
      digitalWrite(M1v, on);  // Motor 1 beginnt zu rotieren
      digitalWrite(M1r, !on);
      digitalWrite(M2v, on);  // Motor 1 beginnt zu rotieren
      digitalWrite(M2r, !on);
      analogWrite(M1PWM, min(abs_v * 255 / MAXVAL, 255));
      analogWrite(M2PWM, min(abs_v * 255 / MAXVAL, 255));
     
      servo1.write(angle * 1.05);
      servo2.write(angle * 1.05);
    }

    /* f[2] = w_z; f[1] = v_x; f[0] = v_y */



    // Serial.println(blueToothVal);

    if (counter == 7) {
      switch (blueToothVal)
      {
        case 4:
          //digitalWrite(messdaten, HIGH);
          servo1.write(pos = (pos > 180 ? 180 : pos + 20));
          break;
        case 8:
          //digitalWrite(messdaten, HIGH)
          servo1.write(pos = (pos < -120 ? 120 : pos - 20));
          break;
        case 42:
        case 1:
          on = 1;
          analogWrite(M1PWM, 255);
          Serial.println("*");
          break;
        case 44:
        case 2:
          on = 0;
          analogWrite(M1PWM, 255);
          break;
        case 43:
        case 0:
          digitalWrite(messdaten, LOW);
          analogWrite(M1PWM, 0);
          //servo1.write(-120);
      }
      digitalWrite(M1v, !on);  // Motor 1 beginnt zu rotieren
      //digitalWrite(M2r, on);
    }
  }

  if (blueToothVal == 42) {
    digitalWrite(led, HIGH);
    delay (500);
    digitalWrite(led, LOW);
    delay(500);
  }

  /* Umwandlung */





  /*
    if (Serial.available())
    {
    blueToothVal = Serial.read();
    counter++;

    if (zaehler == 7) {
      motorVal = blueToothVal;
      /*switch(motorVal)
        {
        case 4:
        digitalWrite(links,HIGH);
        break;
        case 0:
                       digitalWrite(links,LOW);

        }
    }
    }
  */

  if (controlVal == '2') {
    Serial.write("Messdaten anfordern\n");
    digitalWrite(messdaten, HIGH);
    delay (500);
    digitalWrite(messdaten, LOW);
    Serial.write("...\n");
    Serial.write("Messdaten gesendet\n");
    controlVal = 0;
  }

}

#include <Servo.h>
#include <Dabble.h>

Servo servo;
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

int hoch = 44;
int links = 46;
int unten = 48;
int rechts = 50;

int pos = 0;

int in1 = 9;
int in2 = 10;
int GSM1 = 11;

int on = 0;

void setup() {
  Serial.begin(9600);
  Dabble.begin(38400);
  servo.attach(8);
  servo.write(0);
  pinMode(taster, INPUT);
  pinMode(led, OUTPUT);
  pinMode(messdaten, OUTPUT);
  pinMode(links, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(GSM1, OUTPUT);
}

void loop() {



  Dabble.processInput();

  abfrage = digitalRead(taster);
  //delay(100);
  if (abfrage == HIGH) {
    Serial.write("Taste gedrueckt!\n");
    digitalWrite(led, HIGH);
    delay (500);
    digitalWrite(led, LOW);
  }
  else
    digitalWrite(led, LOW);

  if (Serial.available())
  {
    blueToothVal = Serial.read();
    zaehler++;
    counter++;

    /*
      Serial.print(zaehler);
      Serial.print(" : ");
      Serial.println(blueToothVal);
    */
    Serial.println(blueToothVal);
    //Serial.println(zaehler);
    if (zaehler == 6) {
      controlVal = blueToothVal;
      //Serial.println("Richtiger Wert: ");
      //Serial.println(blueToothVal);
      //Serial.println(controlVal);

    }

    if (counter == 7) {
      motorVal = blueToothVal;
      switch (motorVal)
      {
        case 4:
          //digitalWrite(messdaten, HIGH);

          servo.write(pos = (pos > 180 ? 180 : pos + 20));
          break;
        case 8:
          //digitalWrite(messdaten, HIGH)
          servo.write(pos = (pos < -120 ? 120 : pos - 20));
          break;
        case 1:
          on = 1;
          analogWrite(GSM1, 255);
          break;
        case 2:
          on = 0;
          analogWrite(GSM1, 255);
          break;
        case 0:
          digitalWrite(messdaten, LOW);
          analogWrite(GSM1, 0);
          //servo.write(-120);
      }
      digitalWrite(in1, !on);  // Motor 1 beginnt zu rotieren
      digitalWrite(in2, on);
    }
  }
  if (zaehler == 7)
    zaehler = 0;

  if (blueToothVal == 42) {
    digitalWrite(led, HIGH);
    delay (500);
    digitalWrite(led, LOW);
    delay(500);
  }

  if (counter == 8)
    counter = 0;

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



  if (controlVal == 49) {
    for (; i < 180; i++) {
      servo.write(i);
    }
    //blueToothVal = 1;
    //lastValue = blueToothVal;
  }
  else if (controlVal == '0')
  {
    for (; i > -120; i--) {
      servo.write(i);
      //delay(5);
    }
    //lastValue = blueToothVal;
  }

  else if (controlVal == '2') {
    Serial.write("Messdaten anfordern\n");
    digitalWrite(messdaten, HIGH);
    delay (500);
    digitalWrite(messdaten, LOW);
    Serial.write("...\n");
    Serial.write("Messdaten gesendet\n");
    controlVal = 0;
  }

}

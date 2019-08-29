// Gleichstsrommotor 1

int GSM1 = 10;
int in1 = 9;
int in2 = 8;

// Gleichstrommotor 1

int GSM2 = 5;
int in3 = 7;
int in4 = 6;

void setup()
{/*
  pinMode(GSM1, OUTPUT);
  pinMode(GSM2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
*/}
int i = 100;
int on=0;
void loop()
{/*
  digitalWrite(in1, !on);  // Motor 1 beginnt zu rotieren
  digitalWrite(in2, on);
  i=120;
  while (i < 255)
  {
    delay(20);
    analogWrite(GSM1, i);
    i++;
  } 
  while (i > 50)
  {
    analogWrite(GSM1, i);   // Motor 1 soll mit der Geschwindigkeit "200" (max. 255) rotieren
    delay(20);
    i--;
  }
  on=!on;

*/


  /*digitalWrite(in3, HIGH);  // Motor 2 beginnt zu rotieren
    digitalWrite(in4, LOW);

    analogWrite(GSM2, i);   // Motor 2 soll ebenfalls mit der Geschwindigkeit "200" (max. 255) rotieren

    /*digitalWrite(in1, LOW);   // Durch die Veränderung von HIGH auf LOW (bzw. LOW auf HIGH) wird die Richtung der Rotation verändert.
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(2000);

    digitalWrite(in1, LOW);   // Anschließend sollen die Motoren 2 Sekunden ruhen.
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    delay(2000);*/
}

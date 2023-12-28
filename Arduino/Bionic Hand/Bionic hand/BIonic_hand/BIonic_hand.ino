#include <Servo.h>

int servoPin = 2;
Servo testServo;

int value = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  testServo.attach(servoPin);
  testServo.write(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    value = Serial.parseInt();
  }

  if(value == 1)
  {
    testServo.write(0);
  }
  else
  {
    testServo.write(180);
  }
}

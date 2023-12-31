#include <Servo.h>

int servoPin = 2;
Servo testServo;

int value = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  testServo.attach(servoPin);
  testServo.write(0);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    value = Serial.parseInt();
  }

  if(value == 0)
  {
    digitalWrite(LED_BUILTIN, LOW);
    testServo.write(0);
  }


  else
  {
    digitalWrite(LED_BUILTIN, HIGH);
    testServo.write(180);
  }

  delay(50);
}

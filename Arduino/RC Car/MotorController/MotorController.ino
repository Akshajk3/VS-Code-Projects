#include <Servo.h>

int servoPin = 9;

Servo steeringServo;

int x;

int input;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  steeringServo.attach(servoPin);
}

void loop() {
  if (Serial.available() > 0) {
    // Read the data as a string
    String arduinoData = Serial.readStringUntil('\n');
    
    // Convert the string to an integer
    int sensorValue = arduinoData.toInt();

    // Use the sensorValue as needed
    Serial.println(sensorValue);
    x = sensorValue;
  }
  //Serial.println(x);
  steeringServo.write(x);
  delay(100);
}

#include <Servo.h>

int servoPin = 9;
Servo steeringServo;

int x;
int input;

void setup() {
  Serial.begin(9600);
  steeringServo.attach(servoPin);
}

void loop() {
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  if (Serial.available() > 0) {
    String arduinoData = Serial.readStringUntil('\n');
    int sensorValue = arduinoData.toInt();
    Serial.println(sensorValue);
    x = sensorValue;
  }

  if (currentMillis - previousMillis >= 10) {
    previousMillis = currentMillis;

    // Serial.println(x);  // Uncomment if you want to print x
    steeringServo.write(x);
  }
}

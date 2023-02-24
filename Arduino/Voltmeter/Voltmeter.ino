#include <LiquidCrystal.h>

int Vpin = A5;
float voltage;
float volts;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  voltage = analogRead(Vpin);
  volts = voltage/1023*5.0;
  Serial.println(volts);
  lcd.print("Voltage = ");
  lcd.print(volts);
  delay(200);
  lcd.clear();
}

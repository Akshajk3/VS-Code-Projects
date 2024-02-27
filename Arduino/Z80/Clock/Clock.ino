#define CLK_PIN 2

void setup() {
  // put your setup code here, to run once:
  pinMode(CLK_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(CLK_PIN, HIGH);
  delay(100); 
  digitalWrite(CLK_PIN, LOW);
  delay(100);
}

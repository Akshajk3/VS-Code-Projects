const char ADDR[] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53};
const char DATA[] = {22, 24, 26, 28, 30, 32, 34, 36};

#define CLK 2
#define M1 3
#define MREQ 4
#define WR 5
#define RD 6
#define CLK_PIN 7
#define RESET_PIN 8

void setup() {
  for (int i = 0; i < 16; i++)
    pinMode(ADDR[i], INPUT);
  for (int i = 0; i < 8; i++)
    pinMode(DATA[i], INPUT);
  pinMode(CLK, INPUT);
  pinMode(M1, INPUT);
  pinMode(MREQ, INPUT);
  pinMode(WR, INPUT);
  pinMode(RD, INPUT);
  pinMode(RESET_PIN, INPUT);
  Serial.begin(57600);

  attachInterrupt(digitalPinToInterrupt(CLK), onClock, RISING);
}

void onClock()
{
  char output[255];
  unsigned int addr = 0;
  unsigned int data = 0;

  // Print ADDR pin states
  Serial.print("ADDR: ");
  for (int i = 0; i < 16; i++)
  {
    int bit = digitalRead(ADDR[i]) ? 1 : 0;
    addr = (addr << 1) + bit;
    Serial.print(bit);
  }

  // Print DATA pin states
  Serial.print("   DATA: ");
  for (int i = 0; i < 8; i++)
  {
    int bit = digitalRead(DATA[i]) ? 1 : 0;
    data = (data << 1) + bit;
    Serial.print(bit);
  }

  sprintf(output, "   %04x, %c %02x", addr, digitalRead(WR) ? 'r' : 'W', data);
  Serial.println(output);
}

void pulseClock()
{
  digitalWrite(CLK_PIN, HIGH);
  delay(500);
  digitalWrite(CLK_PIN, LOW);
  delay(500);
}

void Reset()
{
  digitalWrite(RESET_PIN, LOW);
  delay(10);
  digitalWrite(RESET_PIN, HIGH);
  Serial.println("Reset");
}

void loop() {
  onClock();
  if (digitalRead(RESET_PIN) == HIGH)
  {
    Serial.println("RESET");
  }
  digitalWrite(RESET_PIN, HIGH);
  pulseClock();
}
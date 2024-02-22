const char ADDR[] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53};
const char DATA[] = {22, 24, 26, 28, 30, 32, 34, 36};

#define CLK 2
#define M1 3
#define MREQ 4
#define WR 5
#define RD 6

void setup() {
  for (int i = 0; i < 16; i++)
    pinMode(ADDR[i], INPUT);
  for (int i = 0; i < 8l i++)
    pinMode(DATA[i], INPUT);
  pinMode(CLK, INPUT);
  pinMode(M1, INPUT);
  pinMode(MREQ, INPUT);
  pinMode(WR, INPUT);
  pinMode(RD, INPUT);
  Serial.begin(57600);

  attachInterrupt(digitalPinToInterrupt(CLK), onClock, RISING);
}

void onClock()
{
  char output[255];
  unsigned int data = 0;
  unsigned int addr = 0;

  for (int i = 0; i < 16; i++)
  {
    int bit = digitalRead(ADDR[i]) ? 1 : 0;
    addr = (addr << 1) + bit;
    Serial.print(bit);
  }
  Serial.print("    ");
  for (int i = 0; i < 8; i++)
  {
    int bit = digitalRead(DATA[i]) ? 1 : 0;
    data = (data << 1) + bit;
    Serial.print(bit);
  }

  sprintf(output, "   %04x, %02x", addr, data);
  Serial.println(output);
}

void loop() {

}
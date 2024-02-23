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
  // put your setup code here, to run once:
  for (int i = 0; i < 16; i++)
    pinMode(ADDR[i], INPUT);
  for (int i = 0; i < 8; i++)
    pinMode(DATA[i], INPUT);
  
  pinMode(CLK, INPUT);
  pinMode(M1, INPUT);
  pinMode(MREQ, INPUT);
  pinMode(WR, INPUT);
  pinMode(RD, INPUT);
  pinMode(CLK_PIN, OUTPUT);
  pinMode(RESET_PIN, OUTPUT);
}

void onClock()
{
  char output[255];
  unsigned int addr = 0;
  unsigned int data = 0;


  Serial.print("ADDR: ")
  for (int i = 0; i < 16; i++)
  {

  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

const char ADDR[] = {23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53};
const char DATA[] = {22, 24, 26, 28, 30, 32, 34, 36};

#define READ_WRITE 2
#define CLK_PIN 3

byte ram[1024];
const unsigned int RAM_START = 0x0000;
byte rom[] = {0xa9, 0xff, 0x8d, 0x02, 0x60, 0xa2, 0x00, 0xbd, 0x1a, 0xc0, 0x8d, 0x00, 0x60, 0xe8, 0x20, 0x18, 0xc0, 0xe0, 0x0a, 0xf0, 0xf0, 0x4c, 0x07, 0xc0, 0xea, 0x60, 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x02, 0xf8, 0x80, 0x90};
const unsigned int ROM_START = 0x8000;

void setup() {
  for (int i = 0; i < 16; i++)
    pinMode(ADDR[i], INPUT);
  for (int i = 0; i < 8; i++)
    pinMode(DATA[i], INPUT);
  
  pinMode(READ_WRITE, INPUT);
  pinMode(CLK_PIN, OUTPUT);

  Serial.begin(57600);
}

void onClock() {
  char output[255];
  unsigned int addr = 0;
  unsigned int data = 0;

  // Print ADDR pin states
  Serial.print("ADDR: ");
  for (int i = 0; i < 16; i++) {
    int bit = digitalRead(ADDR[i]) ? 1 : 0;
    addr = (addr << 1) + bit;
    Serial.print(bit);
  }

  // Print DATA pin states
  Serial.print("    DATA: ");
  for (int i = 0; i < 8; i++) {
    int bit = digitalRead(DATA[i]) ? 1 : 0;
    data = (data << 1) + bit;
    Serial.print(bit);
  }

  char rw = digitalRead(READ_WRITE) ? 'R' : 'W';
  sprintf(output, "   %04x  %c  %02x", addr, rw, data);
  Serial.println(output);
}

void pulseClock() {
  digitalWrite(CLK_PIN, HIGH);
  delay(500); // Adjust this delay according to your clock frequency
  digitalWrite(CLK_PIN, LOW);
  delay(500); // Adjust this delay according to your clock frequency
}

void write(unsigned int data) {
  for (int i = 0; i < 8; i++) {
    pinMode(DATA[i], OUTPUT);
  }

  unsigned int mask = 0b10000000;
  for (int i = 0; i < 8; i++) {
    digitalWrite(DATA[i], data & mask ? 1 : 0);
    mask = mask >> 1;
  }
}

void loop() {
  onClock();
  pulseClock();
}
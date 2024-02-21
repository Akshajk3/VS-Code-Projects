#include <Arduino.h>

const int ADDR[] = {22, 23, 24, 25, 26, 27, 28, 29}; // Z80 A0..A7 pins connected to Arduino pins 22..29
const int DATA[] = {49, 48, 47, 46, 45, 44, 43, 42}; // Z80 D0..D7 pins connected to Arduino pins 49..42
const int CLOCK = 2;
const int READ_WRITE = 3;
const int TRIGGER = 4;

// clock frequency
const int f = 2; // Hz
                        
byte ram[1024]; // RAM: we have 1 MB of RAM
const unsigned int RAM_START = 0x0000; // RAM start address

// 6502 program.
byte rom[] = { 0xa9, 0xff, 0x8d, 0x02, 0x60, 0xa2, 0x00, 0xbd, 0x1a, 0xc0, 0x8d, 0x00, 0x60, 0xe8, 0x20, 0x18, 0xc0, 0xe0, 0x0a, 0xf0, 0xf0, 0x4c, 0x07, 0xc0, 0xea, 0x60, 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 
                        0x02, 0xf8, 0x80, 0x90,  };
const unsigned int ROM_START = 0x8000; // ROM start address

void setup() {
  for (int n = 0; n < 16; n++) {
    pinMode(ADDR[n], INPUT);
  }
  for (int n = 0; n < 8; n++) {
    pinMode(DATA[n], INPUT);
  }
  pinMode(CLOCK, OUTPUT);
  digitalWrite(CLOCK, LOW);
  pinMode(READ_WRITE, INPUT);
  pinMode(TRIGGER, INPUT_PULLUP);

  Serial.begin(57600);
  // load program at 
  Serial.print("ROM size: "); Serial.println(sizeof(rom) / sizeof(rom[0]));
  Serial.print("RAM size: "); Serial.println(sizeof(ram) / sizeof(ram[0]));
}

void loop() {
  // We can step through code by setting frequency low, and touch TRIGGER to low
  while (digitalRead(TRIGGER) == HIGH) {
    // Do nothing
  }
  digitalWrite(CLOCK, LOW);
  // tADS (address setup time is 30ns).
  delayMicroseconds(1); // on 16MHz, 1 cycle is 62.5ns

  // Read data bus
  uint8_t data = readDataBus();

  // is the CPU reading?
  if (digitalRead(READ_WRITE) == HIGH) {
    // read address
    unsigned int address = readAddressBus();

    // Decode address
    if (address == 0xfffc) {        // init vector 
      writeDataBus(0x00FF & ROM_START); // low byte
    } else if (address == 0xfffd) { // init vector 
      writeDataBus(ROM_START >> 8);     // high byte
    } else if ( address >= RAM_START && address <= RAM_START + (sizeof(ram) / sizeof(ram[0]))-1) {
      // Includes stack 0x0100 to 0x01ff
      writeDataBus(ram[address - RAM_START]);
    } else if ( address >= ROM_START && address <= ROM_START + (sizeof(rom) / sizeof(rom[0]))-1) {
      writeDataBus(rom[address - ROM_START]);
    }
  }
  delayMicroseconds(500000 / (f * 2));
  digitalWrite(CLOCK, HIGH);
  
  delayMicroseconds(500000 / (f * 4));
  
  // Handle writes to RAM (includes stack).
  if (digitalRead(READ_WRITE) == LOW) {
    // Read address
    unsigned int address = readAddressBus();

    // Ram writes, includes stack (0x0100-0x01ff)
    if ( address >= RAM_START && address <= RAM_START + (sizeof(ram) / sizeof(ram[0]))-1) {
      ram[address - RAM_START] = data;
    }
  }
  delayMicroseconds(500000 / (f * 4));
}

unsigned int readAddressBus() {
  unsigned int address = 0;
  for (int n = 0; n < 16; n++) {
    int bit = digitalRead(ADDR[n]) ? 1 : 0;
    address = (address << 1) + bit;
  }
  return address;
}

uint8_t readDataBus() {
  uint8_t data = 0;
  for (int n = 0; n < 8; n++) {
    int bit = digitalRead(DATA[n]) ? 1 : 0;
    data = (data << 1) + bit;
  }
  return data;
}

void writeDataBus(uint8_t data) {
  for (int n = 0; n < 8; n++) {
    pinMode(DATA[n], OUTPUT);
    digitalWrite(DATA[n], (data >> n) & 0x01);
  }
}

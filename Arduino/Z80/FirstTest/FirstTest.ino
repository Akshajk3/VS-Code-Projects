// Define pin mappings for Z80 control lines
#define CLK_PIN 10   // Z80 CLK pin connected to Arduino pin 10
#define WR_PIN 18    // Z80 WR pin connected to Arduino pin 18
#define MREQ_PIN A9  // Z80 MREQ pin connected to Arduino pin A9
#define IORQ_PIN A10 // Z80 IORQ pin connected to Arduino pin A10

// Define pin mappings for Z80 data bus
const int Z80_DATA_BUS_SIZE = 8;
const int Z80_ADDR_BUS_SIZE = 8;
const int Z80_DATA_BUS[Z80_DATA_BUS_SIZE] = {49, 48, 47, 46, 45, 44, 43, 42}; // Z80 D0..D7 pins connected to Arduino pins 49..42
const int Z80_ADDR_BUS[Z80_ADDR_BUS_SIZE] = {22, 23, 24, 25, 26, 27, 28, 29}; // Z80 A0..A7 pins connected to Arduino pins 22..29

byte ram[1024]; // RAM: we have 1 MB of ram
const unsigned int RAM_START = 0x0000; // RAM start address

// 6502 program.
byte rom[] = { 0xa9, 0xff, 0x8d, 0x02, 0x60, 0xa2, 0x00, 0xbd, 0x1a, 0xc0, 0x8d, 0x00, 0x60, 0xe8, 0x20, 0x18, 0xc0, 0xe0, 0x0a, 0xf0, 0xf0, 0x4c, 0x07, 0xc0, 0xea, 0x60, 0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 
                        0x02, 0xf8, 0x80, 0x90,  };
const unsigned int ROM_START = 0x8000; // ROM start address

void setup() {
  // Set pin modes
  pinMode(CLK_PIN, OUTPUT);
  pinMode(WR_PIN, OUTPUT);
  pinMode(MREQ_PIN, OUTPUT);
  pinMode(IORQ_PIN, OUTPUT);
  for (int i = 0; i < Z80_DATA_BUS_SIZE; i++) {
    pinMode(Z80_DATA_BUS[i], OUTPUT);
  }
  for (int i = 0; i < Z80_ADDR_BUS_SIZE; i++){
    pinMode(Z80_ADDR_BUS[i], OUTPUT);
  }
  
  // Initialize pins
  digitalWrite(CLK_PIN, LOW);
  digitalWrite(WR_PIN, HIGH); // WR inactive
  digitalWrite(MREQ_PIN, HIGH); // MREQ inactive
  digitalWrite(IORQ_PIN, HIGH); // IORQ inactive
  
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  writeRegisterB(0xFF);

  uint8_t value = readRegisterB();

  Serial.println(value);

  sendClock();
}

void sendClock()
{
  digitalWrite(CLK_PIN, HIGH);
  delay(250);
  digitalWrite(CLK_PIN, LOW);
  delay(250);
}

void writeAddress(uint8_t address)
{
  for (int i = 0; i < Z80_ADDR_BUS_SIZE; i++)
  {
    digitalWrite(Z80_ADDR_BUS[i], (address >> (Z80_ADDR_BUS_SIZE - 1 - i)) & 0x01);
  }
}

void writeRegister(uint8_t reg, uint8_t value) {
  // Activate MREQ and IORQ for write operation
  digitalWrite(MREQ_PIN, LOW);
  digitalWrite(IORQ_PIN, LOW);

  // Set the address lines
  writeAddress(reg);

  digitalWrite(WR_PIN, LOW); // WR should already be low for write operation

  writeData(value);

  digitalWrite(WR_PIN, HIGH);
  digitalWrite(MREQ_PIN, HIGH);
  digitalWrite(IORQ_PIN, HIGH);
}



uint8_t readRegister(uint8_t reg)
{
  writeAddress(reg);

  digitalWrite(MREQ_PIN, HIGH);
  digitalWrite(IORQ_PIN, LOW);

  uint8_t value = readData();

  digitalWrite(IORQ_PIN, HIGH);

  Serial.print("Read value ");
  Serial.print(value, HEX);
  Serial.print(" from address ");
  Serial.println(reg, HEX);

  return value;
}


void writeRegisterB(uint8_t value) {
  // Perform a write operation to Z80 register B
  digitalWrite(WR_PIN, LOW); // Activate WR
  digitalWrite(MREQ_PIN, HIGH); // Deactivate MREQ
  digitalWrite(IORQ_PIN, LOW); // Activate IORQ
  
  // Set the Z80 data bus to the specified value
  writeData(value);
  
  // Deactivate WR and IORQ
  digitalWrite(WR_PIN, HIGH);
  digitalWrite(IORQ_PIN, HIGH);
}

uint8_t readRegisterB() {
  // Perform a read operation from Z80 register B
  digitalWrite(MREQ_PIN, HIGH); // Deactivate MREQ
  digitalWrite(IORQ_PIN, LOW); // Activate IORQ
  
  // Read data from Z80 data bus
  uint8_t value = readData();
  
  // Deactivate IORQ
  digitalWrite(IORQ_PIN, HIGH);
  
  return value;
}

void writeData(uint8_t value) {
  // Write data to Z80 data bus
  for (int i = 0; i < Z80_DATA_BUS_SIZE; i++) {
    digitalWrite(Z80_DATA_BUS[i], (value >> i) & 0x01);
  }
}

uint8_t readData() {
  // Read data from Z80 data bus
  uint8_t value = 0;
  for (int i = 0; i < Z80_DATA_BUS_SIZE; i++) {
    value |= (digitalRead(Z80_DATA_BUS[i]) << i);
  }
  return value;
}

// Define pin mappings for Z80 control lines
#define CLK_PIN 10   // Z80 CLK pin connected to Arduino pin 10
#define WR_PIN 18    // Z80 WR pin connected to Arduino pin 18
#define MREQ_PIN A9  // Z80 MREQ pin connected to Arduino pin A9
#define IORQ_PIN A10 // Z80 IORQ pin connected to Arduino pin A10

// Define pin mappings for Z80 data bus
const int Z80_DATA_BUS_SIZE = 8;
const int Z80_DATA_BUS[Z80_DATA_BUS_SIZE] = {49, 48, 47, 46, 45, 44, 43, 42}; // Z80 D0..D7 pins connected to Arduino pins 49..42

void setup() {
  // Set pin modes
  pinMode(CLK_PIN, OUTPUT);
  pinMode(WR_PIN, OUTPUT);
  pinMode(MREQ_PIN, OUTPUT);
  pinMode(IORQ_PIN, OUTPUT);
  for (int i = 0; i < Z80_DATA_BUS_SIZE; i++) {
    pinMode(Z80_DATA_BUS[i], OUTPUT);
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
  // Wait for input from serial monitor
  if (Serial.available() > 0) {
    // Read input value from serial monitor
    uint8_t inputValue = Serial.parseInt();
    
    // Write input value to Z80 register B
    writeRegisterB(inputValue);
    
    // Read back the value from Z80 register B
    uint8_t readValue = readRegisterB();
    
    // Print the value to the serial monitor
    Serial.print("Value written to Z80 register B: ");
    Serial.println(inputValue);
    Serial.print("Value read from Z80 register B: ");
    Serial.println(readValue);

    // Consume remaining characters in serial buffer
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
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

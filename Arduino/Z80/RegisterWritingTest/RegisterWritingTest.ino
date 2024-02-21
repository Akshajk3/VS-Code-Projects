#include "memory.h"

/*Wiring:
Address Lines:
Arduino Pin 22..29   <--->   Z80 A0..A7

Data Lines:
Arduino Pin 49..42   <--->   Z80 D0..D7

Control lines:
 Arduino Pin 10  <--->  Z80 Pin 6 (CLK)
 Arduino Pin 19  <--->  Z80 Pin 21 (RD)
 Arduino Pin 18  <--->  Z80 Pin 22 (WR)
 Arduino Pin A9  <--->  Z80 Pin 19 (MREQ)
 Arduino Pin A10 <--->  Z80 Pin 20 (IORQ)
 Arduino Pin 40  <--->  Z80 PIN 26 (RESET)
*/

//Working memory
uint8_t memory[1024];

//Z80 Out
//Port D
#define RD_PIN PD2 //(INT2 - Arduino Pin 19) Z80 Pin21
#define WR_PIN PD3 //(INT3 - Arduino Pin 18) Z80 Pin 22
#define RD    ((PIND & (1 << RD_PIN)) == 0) 
#define WR    ((PIND & (1 << WR_PIN)) == 0) 
#define PORT_MASK_D ~((1 << RD_PIN) + ( 1 << WR_PIN));

//Port K
#define MREQ_PIN PK1 //(PCINT17 - Arduino Pin A9) Z80 Pin 19
#define IORQ_PIN PK2 //(PCINT18 - Arduino Pin A10) Z80 Pin 20

#define MREQ  ((PINK & (1 << MREQ_PIN)) == 0) 
#define IORQ  ((PINK & (1 << IORQ_PIN)) == 0) 

#define ADDR PINA //A0..A7
#define ADDR_HI (PINC & (PC0 | PC1)) //A8..A9

//Z80 In
//PortB
#define CLK_PIN PB4 //(OC2A) Z80 Pin 6

//Port G
#define INT_PIN PG0 //Z80 Pin 16, Arduino Pin 41
#define RST_PIN PG1 //Z80 PIN 26, Arduino Pin 40
#define WAIT_PIN PG2 //Z80 Pin 24, Arduino Pin 39
#define RESET(b)  b == 0 ? PORTG |= (1 << RST_PIN) : PORTG &= ~(1 << RST_PIN);  
#define PORT_MASK_G (1 << INT_PIN) + (1 << RST_PIN) + (1 << WAIT_PIN);

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  const long fClk = 1E5;
  //Serial.begin(256000);
  DDRA = 0x00; //Port A (Addr Low) input
  DDRC = 0x00; //Port C (Addr Hi) input
  DDRD &= PORT_MASK_D;
  DDRK = 0x00; //Port K Input (Z80 sysctl out)
  DDRG |= PORT_MASK_G;
  PORTG |= PORT_MASK_G;
  DDRL = 0xff; //Data Bus
  PORTL = 0x00;

  //Pin Interrupts
  EICRA |= (1 << ISC31) + (0 << ISC30) + (1 << ISC21) + (0 << ISC20);
  EIMSK |= (1 << RD_PIN) + (1 << WR_PIN);
    
  //Clock Timer2 
  DDRB |= (1 << CLK_PIN); //Output
  TCCR2A = (0 << COM2A1) + (1 << COM2A0); //Toggle OC2A on Compare Match
  TCCR2A |= (1 << WGM21); //CTC Mode
  TCCR2B = (0 << CS22) + (0 << CS21) + (1 << CS20); //No Prescaling
  OCR2A = 16E6 / (2 * fClk) - 1;
  
  memset(memory, 0, sizeof(memory));
  memcpy(memory, mem, sizeof(mem));
  
  RESET(1);
  delay(1);
  RESET(0);
}

// the loop is empty, because this is interrupt-driven
void loop() {}

//Read data from Data Bus
inline uint8_t DATA_GET() {
	DDRL = 0;
	return PINL;
}

//Write data to Data Bus
inline void DATA_PUT(uint8_t d) {
	DDRL = 0xff;
	PORTL = d;
}

ISR(INT2_vect) {//CPU Reads
  //Serial.println(ADDR);
  if (MREQ) {
    DATA_PUT(memory[ADDR]);
  }
}

ISR(INT3_vect) {//CPU Writes
  if (MREQ) {
    memory[ADDR] = DATA_GET();
  }
  else {//IORQ
    Serial.print((char)DATA_GET());
  }
}
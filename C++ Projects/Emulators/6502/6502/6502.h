#include <iostream>
#include <cstdint>

class CPU
{
public:
    CPU();
    
    void reset();
    void executeInstruction();
    void run();
private:
    uint16_t pc;
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t sp;
    uint8_t status;

    uint8_t read(uint16_t address);
    uint16_t read16(uint16_t address);
    void write(uint16_t address, uint8_t value);
};

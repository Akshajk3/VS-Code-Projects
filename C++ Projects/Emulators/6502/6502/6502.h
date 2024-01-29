#include <iostream>
#include <cstdint>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

class CPU
{
public:
    CPU();
    
    void reset();
    void executeInstruction();
    void run();
private:
    Word pc;
    Word sp;
    Byte a;
    Byte x;
    Byte y;
    Byte sp;
    Byte status;

    uint8_t read(uint16_t address);
    uint16_t read16(uint16_t address);
    void write(uint16_t address, Byte value);

    //OPCODES
    static constexpr Byte LDA_IM = 0xA9;
    static constexpr Byte LDA_ZP = 0xA6;
    static constexpr Byte LDA_ZPX = 0xB5;
    static constexpr Byte JSR = 0x20;
    static constexpr Byte NOP = 0xEE;
};

struct Memory
{
    static constexpr u32 MAX_MEM = 1024 * 64;
};

#include <iostream>
#include <cstdint>

#include "memory.h"

class CPU
{
public:
    CPU();
    
    void reset();
    void executeInstruction();
    void run();
    
    Memory mem;
    
    //OPCODES
    static constexpr Byte LDA_IM = 0xA9;
    static constexpr Byte LDA_ZP = 0xA6;
    static constexpr Byte LDA_ZPX = 0xB5;
    static constexpr Byte JSR = 0x20;
    static constexpr Byte NOP = 0xEE;
    
private:
    Word pc;
    Word sp;
    Byte a;
    Byte x;
    Byte y;
    Byte C : 1;
    Byte Z : 1;
    Byte I : 1;
    Byte D : 1;
    Byte B : 1;
    Byte V : 1;
    Byte N : 1;
    Byte status;
    
    u32 Cycles;

    Byte FetchByte();
    Byte ReadByte(Byte address);
    Word FetchWord();
    void LDASetStatus();
};

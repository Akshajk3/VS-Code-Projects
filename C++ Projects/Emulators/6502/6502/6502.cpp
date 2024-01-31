#include "6502.h"

CPU::CPU()
{}

CPU::~CPU()
{}

void CPU::LDASetStatus()
{
    Z = (a == 0);
    N = (a & 0b10000000) > 0;
}

void CPU::reset()
{
    pc = 0xFFFC;
    sp = 0xFF;
    C = Z = I = D = B = V = N = 0;
    a = x = y = 0;
    mem.Init();
}

Byte CPU::FetchByte()
{
    Byte Data = mem[pc];
    pc++;
    Cycles--;
    return Data;
}

Byte CPU::ReadByte(Byte address)
{
    Byte Data = mem[address];
    Cycles--;
    return Data;
}

Word CPU::FetchWord()
{
    Word Data = mem[pc];
    pc++;
    
    Data |= (mem[pc] << 8);
    pc++;
    
    Cycles -= 2;
    
    return Data;
}

void CPU::PushByte(Byte Value)
{
    mem[0x100 + sp] = Value;
    sp--;
}

Byte CPU::PopByte()
{
    Byte result = mem[0x100 + sp];
    sp++;
    return result;
}

void CPU::executeInstruction(u32 cycles)
{
    Cycles = cycles;

    while (Cycles > 0)
    {
        Byte Ins = FetchByte();
        switch (Ins)
        {
            case LDA_IM:
            {
                Byte Value = FetchByte();
                a = Value;
                LDASetStatus();
            }break;
            case LDA_ZP:
            {
                Byte ZeroPageAddress = FetchByte();
                a = ReadByte(ZeroPageAddress);
                LDASetStatus();
            }break;
            case LDA_ZPX:
            {
                Byte ZeroPageAddress = FetchByte();
                ZeroPageAddress += x;
                Cycles--;
                a = ReadByte(ZeroPageAddress);
                LDASetStatus();
            }break;
            case JSR:
            {
                Word SubAddress = FetchWord();
                mem.WriteWord(pc - 1, sp, Cycles);
                pc = SubAddress;
                Cycles--;
            }break;
            case PHA:
            {
                PushByte(a);
                Cycles -= 3;
            }break;
            case PLA:
            {
                a = PopByte();
                Cycles -= 4;
            }break;
            case NOP:
            {
                Cycles--;
            }break;
            default:
            {
                std::cout << "Instucition Not Handled: " << Ins << std::endl;
            }break;
        }
    }
}

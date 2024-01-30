#include "6502.h"

CPU::CPU()
{}

void CPU::reset()
{
    pc = 0xFFFC;
    sp = 0x0100;
    C = Z = I = D = B = V = N = 0;
    a = x = x = 0;
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

void CPU::executeInstruction()
{
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
            case NOP:
            {
                Cycles--;
            }break;
            default:
            {
                printf("Instucition Not Handled %d", Ins);
            }break;
        }
    }
}

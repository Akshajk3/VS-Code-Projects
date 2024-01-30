#pragma once

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

struct Memory
{
    static constexpr u32 MAX_MEM = 1024 * 64;
    Byte Data[MAX_MEM];
    
    void Init()
    {
        for(u32 i = 0; i < MAX_MEM; i++)
        {
            Data[i] = 0;
        }
    }
    
    // read 1 byte
    Byte operator[](u32 address) const
    {
        return Data[address];
    }
    
    // write 1 byte
    Byte& operator[](u32 address)
    {
        return Data[address];
    }
    
    // write 2 bytes
    void WriteWord(Word Value, u32 address, u32& Cycles)
    {
        Data[address] = Value & 0xFF;
        Data[address + 1] = (Value >> 8);
        Cycles -= 2;
    }
};

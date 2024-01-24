#include <stdio.h>
#include <stdlib.h>


using Byte = unsigned char;
using Word = unsigned int;

using u32 = unsigned int;

struct Mem
{
	static constexpr u32 MAX_MEM = 1024 * 64;
	Byte Data[MAX_MEM];

	void Initialize()
	{
		for (u32 i = 0; i < MAX_MEM; i++)
		{
			Data[i] = 0;
		}
	}

	Byte operator[](u32 Address) const
	{
		return Data[Address];
	}

	Byte& operator[](u32 Address)
	{
		return Data[Address];
	}

	void WriteWord(Word Value, u32 Address, u32& Cycles)
	{
		Data[Address] = Value & 0xFF;
		Data[Address + 1] = (Value << 8);
		Cycles -= 2;
	}
};

struct CPU
{
	Word PC; // program counter
	Word SP; // stack pointer

    // registers
	Byte A, X, Y;
    
    Byte C : 1;
    Byte Z : 1;
    Byte I : 1;
    Byte D : 1;
    Byte B : 1;
    Byte V : 1;
    Byte N : 1;
    
    void Reset(Mem& memory)
    {
        PC = 0xFFFC;
        SP = 0x0100;
        C = Z = I = D = B = V = N = 0;
        A = X = Y = 0;
        memory.Initialize();
    }
};

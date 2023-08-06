#include "instructions.h"
#include "cpu.h"

instruction instructions[0x100] =
{
	{IN_NOP, AM_IMP},
	{IN_DEC, AM_R, RT_B},
	{IN_LD, AM_D8, RT_C},
	{IN_XOR, AM_R, RT_A},
	{IN_JP, AM_D16}
};

instruction* instruction_by_opcode(u8 opcode)
{
	if (instructions[opcode].type == IN_NONE)
	{
		return NULL;
	}

	return &instructions[opcode];
}
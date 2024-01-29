#include "6502.h"

CPU::CPU()
	: pc(0), a(0), x(0), y(0), sp(0xFF), status(0)
{

}

void CPU::reset()
{
	pc = read16(0xFFFC);
	sp = 0xFF;
	status = 0x00;
}

void CPU::executeInstruction()
{
	uint8_t opcode = read(pc);
	pc++;

	

	switch(opcode)
	{
		case 0xEE:
			break;
		default:
			std::cout << "Instruction Not Recognized: " << opcode << std::endl;
			break;
	}
}
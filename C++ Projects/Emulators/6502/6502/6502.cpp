#include "6502.h"

6502::6502()
	: pc(0), a(0), x(0), y(0), sp(0xFF), status(0)
{

}

void 6502::reset()
{
	pc = read16(0xFFFC);
	sp = 0xFF;
	status = 0x00;
}

void executeInstruction()
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

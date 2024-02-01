#include <iostream>
#include <cassert>
#include <iomanip>
#include "6502.h"

int main() {
	CPU cpu;

	cpu.reset();

	cpu.a = 0x55;

	cpu.mem[0xFFFC] = CPU::PHA;
	cpu.pc++;

	cpu.executeInstruction(3);

	assert(cpu.sp == 0xFE);

	return 0;
}

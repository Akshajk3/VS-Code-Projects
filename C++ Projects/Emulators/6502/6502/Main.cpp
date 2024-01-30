#include "6502.h"

int main()
{
    CPU cpu;
    cpu.reset();
    cpu.mem[0xFFFC] = cpu.JSR;
    cpu.mem[0xFFFD] = 0x42;
    cpu.mem[0xFFFE] = 0x42;
    cpu.mem[0x4242] = cpu.LDA_IM;
    cpu.mem[0x4243] = 0x84;
    cpu.executeInstruction();
}

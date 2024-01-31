#include <cassert>
#include "6502.h"

int main() {
    CPU cpu;
    cpu.reset();
    
    cpu.a = 0x42;
    cpu.mem[0xFFFC] = CPU::PHA;
    cpu.executeInstruction(3);
    
    assert(cpu.sp == 0xFE);

    std::cout << "Test Cases passed!" << std::endl;

    return 0;
}

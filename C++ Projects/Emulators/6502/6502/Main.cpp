#include <cassert>
#include "6502.h"

int main() {
    // Initialize and reset the CPU
    CPU cpu;
    cpu.reset();

    // Test CPU::PHA and CPU::PLA instructions
    cpu.a = 0x42;  // Set accumulator to 0x42

    // Execute CPU::PHA instruction
    cpu.executeInstruction(3);  // CPU::PHA takes 3 cycles
    assert(cpu.sp == 0xFE);     // Check if stack pointer decreased

    // Execute CPU::PLA instruction
    cpu.executeInstruction(4);  // CPU::PLA takes 4 cycles
    assert(cpu.sp == 0xFF);     // Check if stack pointer increased
    assert(cpu.a == 0x42);      // Check if accumulator contains the correct value

    std::cout << "Test cases passed!" << std::endl;

    return 0;
}

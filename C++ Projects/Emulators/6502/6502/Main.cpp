#include <cassert>

#include "6502.h"

int main() {
    // Initialize and reset the CPU
    CPU cpu;
    cpu.reset();

    // Test LDA immediate
    cpu.mem[0xFFFC] = CPU::LDA_IM;  // LDA immediate instruction
    cpu.mem[0xFFFD] = 0x42;     // Value to load
    cpu.executeInstruction(2);  // Execute one instruction
    assert(cpu.a == 0x42);      // Check if accumulator contains the correct value

    std::cout << "Simple test case passed!" << std::endl;

    return 0;
}

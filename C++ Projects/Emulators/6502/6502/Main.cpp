#include <cassert>
#include <iostream>
#include "6502.h"

int main() {
    CPU cpu;
    cpu.reset();

    // Test LDA_ZPX instruction
    cpu.mem[0xFFFC] = CPU::LDA_ZPX;  // Set the opcode for LDA_ZPX at the reset vector
    cpu.mem[0xFFFD] = 0x20;          // Zero Page address
    cpu.x = 0x03;                    // X Index
    cpu.mem[0x0023] = 0x42;          // Value to load at Zero Page address + X Index

    // Execute the instruction with enough cycles
    cpu.executeInstruction(4); // LDA_ZPX takes 4 cycles

    // Check if the accumulator contains the correct value
    assert(cpu.a == 0x42);

    std::cout << "Test case passed!" << std::endl;

    return 0;
}


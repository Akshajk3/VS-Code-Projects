#pragma once

#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <fstream>

class Emulator
{
public:
	Emulator();
	void loadRom(const char* filePath);
	void run();

private:
	uint8_t memory[4096];
	uint8_t registers[16];
	uint8_t sp;
	uint16_t pc;
	uint16_t I;
	uint8_t delayTimer;
	uint8_t soundTimer;
	uint8_t keys[16];
	uint8_t display[64][32];
};

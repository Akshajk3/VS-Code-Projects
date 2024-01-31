#pragma once

#include <iostream>

class CPU
{
public:
	CPU();
	~CPU();

	void LoadROM(const char* romName);
	void EmulateCycle();
	void PressKey(uint8_t key);
	void ReleaseKey(uint8_t key);

private:
	uint8_t mem[4096];
	uint8_t registers[16];
	uint16_t I;
	uint8_t delayTimer;
	uint8_t soundTimer;
	uint16_t pc;
	uint16_t* sp;
	uint16_t stack[16];
	uint8_t keys[16];
	bool display[64 * 32];
	uint32_t pixelColors[64 * 32];
	const char* rom_name;
	bool draw;

	// OPCodes
	uint16_t opcode;
	uint16_t NNN;
	uint8_t NN;
	uint8_t N;
	uint8_t X;
	uint8_t Y;

	int window_width;
	int window_height;
	int scale_factor;
};

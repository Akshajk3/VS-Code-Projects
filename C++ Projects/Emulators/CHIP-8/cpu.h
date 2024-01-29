#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstdlib>
#include <ctime>

constexpr int MEMORY_SIZE = 4096;
constexpr int DISPLAY_WIDTH = 64;
constexpr int DISPLAY_HEIGHT = 32;
constexpr int SCREEN_SCALE = 10;

constexpr int SCREEN_WIDTH = DISPLAY_WIDTH * SCREEN_SCALE;
constexpr int SCREEN_HEIGHT = DISPLAY_HEIGHT * SCREEN_SCALE;

class CPU
{
public:
	CPU();
	void loadFont();
	void loadROM(const char* romPath);
	void run();

private:
	uint8_t memory[MEMORY_SIZE];
	uint8_t registers[16];
	uint16_t pc;
	uint16_t sp;
	uint16_t stack[16];
	uint8_t display[DISPLAY_HEIGHT][DISPLAY_WIDTH];
	uint8_t keys[16];
	uint8_t delayTimer;
	uint8_t soundTimer;
};

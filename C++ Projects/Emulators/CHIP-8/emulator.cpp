#include "emulator.h"

Emulator::Emulator()
{
	for(int i = 0; i < 4096; i++)
	{
		memory[i] = 0;
	}

	for(int i = 0; i < 16; i++)
	{
		registers[i] = 0;
	}

	
}

void Emulator::loadROM(const char* filePath)
{
	std::ifstream romFile = (filePath, std::ios::binary);	
}

void Emulator::run()
{

}

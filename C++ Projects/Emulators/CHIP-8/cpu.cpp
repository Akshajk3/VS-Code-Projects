#include "cpu.h"

CPU::CPU()
{
	std::fill_n(memory, MEMORY_SIZE, 0);
	std::fill_n(registers, 16, 0);
	pc = 0x200;
	sp = 0;
	std::fill_n(stack, 16, 0);
	std::fill_n(display[0], DISPLAY_HEIGHT * DISPLAY_WIDTH, 0);
	std::fill_n(keys, 16, 0);
	delayTimer = 0;
	soundTimer = 0;

	std::srand(std::time(nullptr));

	loadFont();
}

void CPU::loadFont()
{

}

void CPU::loadROM(const char* filePath)
{
	std::ifstream romFile(filePath, std::ios::binary | std::ios::ate);
	if(!romFile.is_open())
	{
		std::cout << "Failed to Open Rom File" << filePath << std::endl;
		std::exit(EXIT_FAILURE);
	}

	std::streamsize size = romFile.tellg();
	romFile.seekg(0, std::ios::beg);

	std::vector<char> buffer(size);
	if(!romFile.read(buffer.data(), size))
	{
		std::cout << "Failed to read ROM file." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	for(std::size_t i = 0; i < buffer.size(); i++)
	{
		memory[0x200 + i] = buffer[i];
	}

	romFile.close();
}

#include "olc6502.h"

olc6502::olc6502()
{

}

olc6502::~olc6502()
{

}

uint8_t olc6502::read(uint16_t address)
{
	return bus->read(address, false);
}

void olc6502::write(uint16_t address, uint8_t data)
{
	bus->write(address, data);
}
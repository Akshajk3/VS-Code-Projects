#pragma once
#include <cstdint.h>

class Bus
{
public:
	Bus();
	~Bus();

	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool ReadOnly = false);
};

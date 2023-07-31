#include "bus.h"

// 0x0000 - 0x3FFF : ROM Bank 0
// 0x4000 - 0x7FFF : ROM Bank 1
// 0x8000 - 0x97FF : CHR RAM
// 0x9800 - 0x98FF : BG MAP 1
// 0x9C00 - 0x9FFF : BG MAP 2
// 0xA000 - 0xBFFF : CARTRIDGE RAM
// 0xC000 - 0xCFFF : RAM BANK 0
// 0xD000 - 0xDFFF : RAM BAND 1-7 - SWITCHABLE - COLOR ONLY
// 0xE000 - 0xFDFF : RESERVED - ECHO RAM
// 0xFE00 - 0xFE9F : OBJECT ATTRIBUTE MEMORY
// 0xFEA0 - 0xFEFF : RESERVED - UNUSABLE
// 0xFF00 - 0xFF7F : I/O REGISTERS
// 0xFF80 - 0xFFFE : ZERO PAGE

u8 bus_read(u16 address)
{
    if(address < 0x8000)
    {
        // ROM Data
        return cart_read(address);
    }

    NO_IMPL
}

void bus_write(u16 address, u8 value)
{
    if(address < 0x8000)
    {
        // ROM Data
        cart_write(address, value);
    }
}
#include <iostream>

#include "WADLoader.h"

int main()
{
    WADLoader wadLoader("wad/DOOM.WAD");
    wadLoader.LoadWAD();
    return 0;
}

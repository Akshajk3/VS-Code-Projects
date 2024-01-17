#include <iostream>

#include "WADLoader.h"
#include "Map.h"


int main()
{
	WADLoader wadLoader("wad/DOOM.WAD");
	wadLoader.LoadWAD();

	Map map("E1M1");
	wadLoader.LoadMapData(map);
	return 0;
}

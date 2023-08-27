#include "Tilemap.h"

int lvl1[10][10] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
};

Tilemap::Tilemap(std::map<std::string, std::vector<SDL_Texture*>> sprites, int tile_size)
	: assets(sprites), tile_size(tile_size)
{
	
}

void Tilemap::render()
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			int tileIndex = lvl1[x][y];
			SDL_Rect srcRect = { 0, 0, tile_size, tile_size };
			SDL_Rect destRect = { x * tile_size, y * tile_size, tile_size, tile_size };
		}
	}
}
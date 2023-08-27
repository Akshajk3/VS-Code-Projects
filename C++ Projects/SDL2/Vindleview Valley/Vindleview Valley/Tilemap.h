#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <map>

class Tilemap
{
public:
	Tilemap(std::map<std::string, std::vector<SDL_Texture*>> sprites, int tile_size = 16);

	void render();
private:
	std::map<std::string, std::vector<SDL_Texture*>> assets;
	int tile_size;
	int tileMap[10][10];
};
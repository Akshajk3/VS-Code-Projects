#pragma once

#include <iostream>
#include <vector>

#include "Item.h"

class Inventory
{
public:
	Inventory(std::vector<SDL_Texture*> tiles);

	void addItem(Item& item);
	void removeItem(int index);
	void render(SDL_Renderer* renderer);
    
    bool show = false;

private:
	std::vector<Item> items;
	SDL_Rect InventoryRect;
	std::vector<SDL_Texture*> invTiles;

	SDL_Rect src, dest;
};

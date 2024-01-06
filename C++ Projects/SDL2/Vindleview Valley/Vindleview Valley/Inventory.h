#pragma once

#include <iostream>
#include <vector>

#include "Item.h"

class Inventory
{
public:
	Inventory(std::vector<SDL_Texture*> tiles);

	void addItem(Item& item);
	void removeItem(int index, int count);
	void render(SDL_Renderer* renderer);
	bool checkClick(SDL_Rect mouseRect);

    bool show = false;

private:
	std::vector<Item> items;
	SDL_Rect InventoryRect;
	std::vector<SDL_Texture*> invTiles;

	SDL_Rect src, dest;

	int col = 0;
	int row = -1;
};

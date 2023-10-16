#pragma once

#include <iostream>
#include <vector>

#include "Item.h"

class Inventory
{
public:
	Inventory();

	void addItem(Item& item);
	void removeItem(int index);
	void render(SDL_Renderer* renderer);
    
    bool show = false;

private:
	std::vector<Item> items;
	SDL_Rect InventoryRect;
};

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

private:
	std::vector<Item> items;
};
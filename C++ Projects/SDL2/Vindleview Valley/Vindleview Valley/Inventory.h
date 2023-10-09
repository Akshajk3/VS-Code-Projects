#pragma once

#include <iostream>
#include <vector>

#include "Item.h"

class Inventory
{
public:
	Inventory();

	void addItem(const Item& item);
	void removeItem(int index);
	void render();

private:
	std::vector<Item> items;
};
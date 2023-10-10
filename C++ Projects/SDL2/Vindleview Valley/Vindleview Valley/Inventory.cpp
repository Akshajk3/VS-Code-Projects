#include "Inventory.h"

Inventory::Inventory()
{

}

void Inventory::addItem(Item& item)
{
    item.addCount();
    item.setIndex(items.size() - 1);
    items.push_back(item);
}

void Inventory::removeItem(int index)
{
    items.pop_back();
}

void Inventory::render(SDL_Renderer* renderer)
{
    for(Item& item : items)
    {
        int offest[2] = {0, 0};
        item.render(renderer, offest);
    }
}
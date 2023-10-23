#include "Inventory.h"

Inventory::Inventory(std::vector<SDL_Texture*> tiles)
    : invTiles(tiles)
{
    src.x = 0;
    src.y = 0;
    src.w = dest.w = 96;
    src.h = dest.h = 96;

    dest.x = 800/2 - (src.w / 2);
    dest.y = 600/2 - (src.h / 2);
}

void Inventory::addItem(Item& item)
{
    item.addCount();
    item.setIndex(items.size() - 1.0f);
    items.push_back(item);
}

void Inventory::removeItem(int index)
{
    items.pop_back();
}

void Inventory::render(SDL_Renderer* renderer)
{   
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            dest.x = (800 - 352) / 2 + (i * 96) - (src.w / 2);
            dest.y = (600 - 192) / 2 + (j * 96) - (src.h / 2);
            SDL_RenderCopy(renderer, invTiles[0], &src, &dest);

            for (Item& item : items)
            {
                int offest[2] = { 0, 0 };
                item.render(renderer, offest);
            }
        }
    }
}

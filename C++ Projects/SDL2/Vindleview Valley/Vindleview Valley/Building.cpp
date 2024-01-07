#include "Building.h"


Building::Building(int p_x, int p_y, SDL_Texture* tex, SDL_Renderer* ren, bool place, bool transparent)
    : x(p_x), y(p_y), texture(tex), renderer(ren), placed(place)
{
    src.x = 0;
    src.y = 0;
    
    src.w = dest.w = 48 * 4;
    src.h = dest.h = 48 * 4;
    dest.x = x - (src.w / 2);
    dest.y = y - (src.h / 2);

    if (transparent == true)
    {
        SDL_SetTextureAlphaMod(texture, 100);
    }
    else
    {
        SDL_SetTextureAlphaMod(texture, 255);
    }
};

void Building::update(int mouseX, int mouseY)
{
    if(placed == false)
    {
        x = mouseX;
        y = mouseY;

        dest.x = x - (src.w / 2);
        dest.y = y - (src.h / 2);
    }
}

void Building::render(int cameraX, int cameraY)
{
    dest.x = x - cameraX;
    dest.y = y - cameraY;

    SDL_RenderCopy(renderer, texture, &src, &dest);
}

bool Building::isPlaced()
{
    return placed;
}

/*
void Building::Place()
{
    if (placed != true)
    {
        placed = true;
        SDL_SetTextureAlphaMod(texture, 255);
    }
}
*/
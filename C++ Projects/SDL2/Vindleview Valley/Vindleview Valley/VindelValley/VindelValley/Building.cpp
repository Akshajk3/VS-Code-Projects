#include "Building.h"


Building::Building(int p_x, int p_y, SDL_Texture* tex, SDL_Renderer* ren)
    : x(p_x), y(p_y), texture(tex), renderer(ren)
{
    src.x = 0;
    src.y = 0;
    
    src.w = dest.w = 48;
    src.h = dest.h = 48;
    dest.x = x - (src.w / 2);
    dest.y = y - (src.h / 2);
};

void Building::render()
{
    SDL_RenderCopy(renderer, texture, &src, &dest);
}

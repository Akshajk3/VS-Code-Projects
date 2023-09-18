#include "Item.h"

Item::Item(float p_x, float p_y, std::string p_type, float animSpeed, SDL_Texture* tex)
    : x(p_x), y(p_y), type(p_type), bobSpeed(animSpeed), texture(tex)
{
    src.x = 0;
    src.y = 0;
    
    src.w = dest.w = 32;
    src.h = dest.h = 32;
    dest.x = x;
    dest.y = y;
}

void Item::update()
{
    if (bobUp)
    {
        dest.y -= bobSpeed;
        y -= bobSpeed;
    }
    else
    {
        dest.y += bobSpeed;
        y += bobSpeed;
    }
    
    if (y < initialYPos - 1)
    {
        bobUp = false;
    }
    else if (y > initialYPos + 1)
    {
        bobUp = true;
    }
}

void Item::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, &src, &dest);
}

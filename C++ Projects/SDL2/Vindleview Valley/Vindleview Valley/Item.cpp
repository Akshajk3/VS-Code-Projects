#include "Item.h"

Item::Item(float p_x, float p_y, std::string p_type, float animSpeed, SDL_Texture* tex)
    : x(p_x), y(p_y), type(p_type), bobSpeed(animSpeed), texture(tex)
{
    src.x = x;
    
    src.w = dest.w = 32;
    src.h = dest.h = 32;
    dest.x = 0;
    dest.x = 0;
}

void Item::update()
{
    if (bobUp)
    {
        y -= bobSpeed;
    }
    else
    {
        y += bobSpeed;
    }
    
    if (y <= initialYPos - 10)
    {
        bobUp = false;
    }
    else if (y >= initialYPos + 10)
    {
        bobUp = true;
    }
}

void Item::render()
{
    
}

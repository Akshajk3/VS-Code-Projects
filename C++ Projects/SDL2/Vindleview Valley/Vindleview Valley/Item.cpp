#include "Item.h"

Item::Item(float p_x, float p_y, std::string p_type, float animSpeed, SDL_Texture* tex, float scale)
    : x(p_x), y(p_y), type(p_type), bobSpeed(animSpeed), texture(tex)
{
    src.x = 0;
    src.y = 0;
    
    src.w = dest.w = 32 * scale;
    src.h = dest.h = 32 * scale;
    dest.x = x - (src.w / 2);
    dest.y = y - (src.h / 2);
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

    itemTimer += 1;
}

void Item::render(SDL_Renderer* renderer, int offset[2])
{
    dest.x = x - offset[0];
    dest.y = y - offset[1];

    SDL_RenderCopy(renderer, texture, &src, &dest);
}

void Item::addCount()
{
    count += 1;
}

void Item::setIndex(int index)
{
    
}

void Item::setPos(int p_x, int p_y)
{
    x = p_x;
    y = p_y;

    dest.x = x - (src.w / 2);
    dest.y = y - (src.h / 2); 
}

bool Item::checkMouse(SDL_Rect mouseRect)
{
    return (mouseRect.x < dest.x + dest.w &&
        mouseRect.x + mouseRect.w > dest.x &&
        mouseRect.y < dest.y + dest.h &&
        mouseRect.y + mouseRect.h > dest.y);
}

std::string Item::getType()
{
    return type;
}

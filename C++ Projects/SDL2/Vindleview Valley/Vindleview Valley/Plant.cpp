#include "Plant.h"

Plant::Plant(float p_x, float p_y, std::string p_type, int gTime, Tilemap* plantMap)
    : x(p_x), y(p_y), type(p_type), growTime(gTime), tilemap(plantMap), lastUpdateTime(SDL_GetTicks())
{
    if (type == "wheat")
    {
        startStage = 3;
    }
    if (type == "beet")
    {
        startStage = 7;
    }
    
    stage = startStage;
}

void Plant::grow()
{
    int newStage;
    newStage = std::min(startStage + 3, stage + 1);
    
    tilemap->setTile(x, y, newStage);
    
    stage += 1;
    
    lastUpdateTime = currentTime;
}

void Plant::update()
{
    currentTime = SDL_GetTicks();
    
    if (currentTime - lastUpdateTime > growTime)
    {
        grow();
    }
}

int Plant::getX()
{
    return x;
}

int Plant::getY()
{
    return y;
}

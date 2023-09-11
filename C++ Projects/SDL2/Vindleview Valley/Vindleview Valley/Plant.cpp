#include "Plant.h"

Plant::Plant(float p_x, float p_y, std::string p_type, int gTime, Tilemap plantMap)
    : x(p_x), y(p_y), type(p_type), growTime(gTime), tilemap(plantMap)
{
    if (type == "wheat")
    {
        startStage = 3;
    }
    
    stage = startStage;
    growTimer = growTime;
}

void Plant::grow()
{
    int newStage;
    newStage = std::min(7, stage + 1);
    
    //std::cout << newStage << std::endl;
    
    //std::cout << tilemap.getTile(x, y) << std::endl;
    
    tilemap.setTile(x, y, newStage);
    growTimer = growTime;
    
    stage += 1;
}

void Plant::update()
{
    growTimer -= 1;
    
    //std::cout << growTimer << std::endl;
    
    if (growTimer <= 0)
    {
        grow();
    }
}

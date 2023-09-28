#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "Tilemap.h"

class Plant
{
public:
    Plant(float p_x, float p_y, std::string p_type, int gTime, Tilemap* plantMap);
    void grow();
    void update();
    int getX();
    int getY();
    
private:
    int growTime;
    Uint32 lastUpdateTime;
    Uint32 currentTime;
    std::string type;
    int x, y;
    int stage;
    int startStage;
    Tilemap* tilemap;
};

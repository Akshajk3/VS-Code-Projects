#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

class Item
{
public:
    Item(float p_x, float p_y, std::string p_type, float animSpeed, SDL_Texture* p_tex);
    
    void update();
    void render();
    
private:
    float x, y;
    float initialYPos;
    std::string type;
    SDL_Texture* texture;
    bool bobUp;
    float bobSpeed;
    SDL_Rect src, dest;
};

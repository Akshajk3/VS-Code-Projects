#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Item
{
public:
    Item(float p_x, float p_y, std::string p_type, float animSpeed, SDL_Texture* p_tex);
    
    void update();
    void render(SDL_Renderer* renderer, int offset[2]);
    
private:
    float x, y;
    float initialYPos;
    std::string type;
    SDL_Texture* texture;
    bool bobUp;
    float bobSpeed;
    SDL_Rect src, dest;
    int itemTimer = 0;
};

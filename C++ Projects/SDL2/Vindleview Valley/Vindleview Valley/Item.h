#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Item
{
public:
    Item(float p_x, float p_y, std::string p_type, float animSpeed, SDL_Texture* p_tex, float scale = 1);
    
    void update();
    void render(SDL_Renderer* renderer, int offset[2]);
    void addCount();
    void setIndex(int index);
    void setPos(int x, int y);
    bool checkMouse(SDL_Rect mouseRect);
    
    bool dead = false;
    
    std::string getType();
    
private:
    float x, y;
    float initialYPos;
    std::string type;
    SDL_Texture* texture;
    bool bobUp;
    float bobSpeed;
    SDL_Rect src, dest;
    int itemTimer = 0;
    int count = 0;
    int index = 0;
};

#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Animation.h"
#include "TextureManager.h"

class Entity
{
public:
    Entity(float p_x, float p_y, SDL_Renderer* ren, std::string type, std::map<std::string, std::vector<SDL_Texture*>> assets);
    float getX();
    float getY();
    SDL_Rect getCurrentFrame();
    Animation getAnimation();
    void setAction(std::string act);
    
    void update();
    
    std::string direction = "left";
    float x, y;
    std::string action;
    
private:
    SDL_Rect currentFrame;
    Animation animation;
    std::string type;
    std::string oldDirection = direction;
    SDL_Renderer* renderer;
    std::map<std::string, std::vector<SDL_Texture*>> asset;
};

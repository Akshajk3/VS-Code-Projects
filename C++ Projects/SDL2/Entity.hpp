#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Entity
{
    public:
        Entity(double d_x, double d_y, SDL_Texture* p_tex);
    private:
        double x, y;
        SDL_Rect currentFrame;
        SDL_Texture* tex;
};
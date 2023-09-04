#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RenderWindow
{
public:
    RenderWindow(const char* windowName, int width, int height);
    void cleanUp();
    void clear();
    void render();
    void display();
    
    SDL_Renderer* renderer;
private:
    SDL_Window* window;
    int currentFrame = 0;
};

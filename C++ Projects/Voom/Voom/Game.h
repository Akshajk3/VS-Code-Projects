#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "DoomEngine.h"

class Game
{
public:
    Game();
    ~Game();
    
    void HandelInput();
    void Render();
    void Update();
    void Delay();
    
    bool IsOver();
    bool Init();
    
private:
    int WindowWidth;
    int WindowHeight;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    DoomEngine* doomEngine;
};

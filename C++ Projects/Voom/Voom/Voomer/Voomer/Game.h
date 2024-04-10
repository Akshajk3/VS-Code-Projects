#pragma once

#include <SDL2/SDL.h>

#include "DoomEngine.h"

class Game
{
public:
    Game();
    virtual ~Game();
    
    void ProcessInput();
    void Render();
    void Update();
    void Delay();
    void RenderPresent();
    void RenderClear();
    
    bool IsOver();
    bool Init();

protected:
    int m_WindowWidth;
    int m_WindowHeight;
    
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    DoomEngine* m_DoomEngine;
};

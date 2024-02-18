#pragma once

#include <iostream>
#include <SDL2/SDL.h>

#include "Map.h"
#include "WADLoader.h"

class DoomEngine
{
public:
    DoomEngine();
    ~DoomEngine();
    
    virtual void Render(SDL_Renderer* renderer);
    virtual void KeyPressed(SDL_Event& event);
    virtual void KeyReleased(SDL_Event& event);
    virtual void Update();
    virtual void Quit();
    
    virtual bool IsOver();
    virtual bool Init();
    
    virtual int GetRenderWidth();
    virtual int GetRenderHeight();
    virtual int GetTimePerFrame();
    
    virtual std::string GetName();
    virtual std::string GetWADFileName();
private:
    int RenderWidth;
    int RenderHeight;
    
    bool isOver;
    
    WADLoader wadLoader;
    Map* map;
};

#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "Map.h"
#include "WADLoader.h"
#include "Player.h"
#include "ViewRenderer.h"

class DoomEngine
{
public:
    DoomEngine(SDL_Renderer* renderer);
    ~DoomEngine();
    
    virtual void Render();
    virtual void KeyPressed(SDL_Event &event);
    virtual void KeyReleased(SDL_Event &event);
    virtual void Quit();
    virtual void Update();
    
    virtual bool IsOver();
    virtual bool Init();
    
    virtual int GetRenderWidth();
    virtual int GetRenderHeight();
    virtual int GetTimePerFrame();
    
    virtual std::string GetName();
    virtual std::string GetWADFileName();
    
protected:
    int m_RenderWidth;
    int m_RenderHeight;
    
    bool m_IsOver;
    bool m_RenderAutoMap;
    
    SDL_Renderer* m_Renderer;
    WADLoader m_WADLoader;
    Map* m_Map;
    Player* m_Player;
    Things* m_Things;
    ViewRenderer* m_ViewRenderer;
};

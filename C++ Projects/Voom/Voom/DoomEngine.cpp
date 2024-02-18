#include "DoomEngine.h"

DoomEngine::DoomEngine()
    : isOver(false), RenderWidth(320), RenderHeight(200)
{
    map = new Map("E1M1");
}

DoomEngine::~DoomEngine()
{
    
}

bool DoomEngine::Init()
{
    wadLoader.SetWADFilePath(GetWADFileName());
    wadLoader.LoadWAD();
    wadLoader.LoadMapData(map);
    return true;
}

std::string DoomEngine::GetWADFileName()
{
    return "wad/DOOM1.WAD";
}

void DoomEngine::Render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

void DoomEngine::KeyPressed(SDL_Event &event)
{
    switch (event.key.keysym.sym)
    {
        case SDLK_UP:
            break;
        case SDLK_DOWN:
            break;
        case SDLK_LEFT:
            break;
        case SDLK_RIGHT:
            break;
        case SDLK_ESCAPE:
            Quit();
            break;
        default: break;
    }
}

void DoomEngine::KeyReleased(SDL_Event &event)
{
    
}

void DoomEngine::Quit()
{
    isOver = true;
}

void DoomEngine::Update()
{
    
}

bool DoomEngine::IsOver()
{
    return isOver;
}

int DoomEngine::GetRenderWidth()
{
    return RenderWidth;
}

int DoomEngine::GetRenderHeight()
{
    return RenderHeight;
}

int DoomEngine::GetTimePerFrame()
{
    return 1000 / 60;
}

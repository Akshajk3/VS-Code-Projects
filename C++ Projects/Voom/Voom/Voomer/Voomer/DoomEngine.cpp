#include "DoomEngine.h"

DoomEngine::DoomEngine(SDL_Renderer* renderer)
    : m_Renderer(renderer), m_IsOver(false), m_RenderWidth(320), m_RenderHeight(200), m_Map(nullptr), m_RenderAutoMap(false)
{
    
}

DoomEngine::~DoomEngine()
{
    delete m_Map;
}

std::string DoomEngine::GetWADFileName()
{
    return "wad/DOOM.WAD";
}

bool DoomEngine::Init()
{
    m_ViewRenderer = new ViewRenderer(m_Renderer);
    
    m_Player = new Player(m_ViewRenderer, 1);
    m_Map = new Map("E1M1", m_Player, m_ViewRenderer);
    
    m_WADLoader.SetWADFilePath(GetWADFileName());
    m_WADLoader.LoadWAD();
    
    m_WADLoader.LoadMapData(m_Map);
    return true;
}

void DoomEngine::Render()
{
    SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(m_Renderer);
    m_Map->RenderAutoMap();
}

void DoomEngine::KeyPressed(SDL_Event &event)
{
    switch (event.key.keysym.sym)
    {
        case SDLK_UP:
            break;
        case SDLK_DOWN:
            break;
        case SDLK_RIGHT:
            m_Player->RotateRight();
            break;
        case SDLK_LEFT:
            m_Player->RotateLeft();
            break;
        case SDLK_TAB:
            m_RenderAutoMap = true;
            break;
        case SDLK_ESCAPE:
            Quit();
            break;
        default:
            break;
    }
}

void DoomEngine::KeyReleased(SDL_Event &event)
{
    
}

void DoomEngine::Quit()
{
    m_IsOver = true;
}

void DoomEngine::Update()
{
    
}

bool DoomEngine::IsOver()
{
    return m_IsOver;
}

int DoomEngine::GetRenderWidth()
{
    return m_RenderWidth;
}

int DoomEngine::GetRenderHeight()
{
    return m_RenderHeight;
}

int DoomEngine::GetTimePerFrame()
{
    return 1000 / 60;
}

std::string DoomEngine::GetName()
{
    return "Voom";
}

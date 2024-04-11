#include "DoomEngine.h"

DoomEngine::DoomEngine(SDL_Renderer* renderer)
    : m_Renderer(renderer), m_IsOver(false), m_RenderWidth(320), m_RenderHeight(200), m_Map(nullptr), m_RenderAutoMap(false)
{
    
}

DoomEngine::~DoomEngine()
{
    delete m_Map;
    delete m_Player;
    delete m_ViewRenderer;
}

std::string DoomEngine::GetWADFileName()
{
    return "wad/DOOM.WAD";
}

bool DoomEngine::Init()
{
    m_ViewRenderer = new ViewRenderer(m_Renderer);
    m_Things = new Things();
    
    m_Player = new Player(m_ViewRenderer, 1);
    m_Map = new Map("E1M1", m_Player, m_ViewRenderer, m_Things);

    m_ViewRenderer->Init(m_Map, m_Player);
    
    m_WADLoader.SetWADFilePath(GetWADFileName());
    m_WADLoader.LoadWAD();
    m_WADLoader.LoadMapData(m_Map);

    Thing thing = (m_Map->GetThing())->GetThingByID(m_Player->GetID());

    m_Player->Init(thing);
    m_Map->Init();

    return true;
}

void DoomEngine::Render()
{
    m_ViewRenderer->InitFrame();
    m_ViewRenderer->Render(m_RenderAutoMap);
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
    switch (event.key.keysym.sym)
    {
    case SDLK_TAB:
        m_RenderAutoMap = false;
        break;

    default:
        break;
    }
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

#include "DoomEngine.h"

DoomEngine::DoomEngine(SDL_Renderer* renderer)
	: m_Renderer(renderer), m_bIsOver(false), m_iRenderWidth(320), m_iRenderHeight(200)
{
}

DoomEngine::~DoomEngine()
{
	
}

std::string DoomEngine::GetWADFileName()
{
	return "wad/DOOM.WAD";
}

std::string DoomEngine::GetName()
{
	return "Voom";
}

bool DoomEngine::Init()
{
	m_Player = new Player(1);
	m_pMap = new Map(m_Renderer, "E1M1", m_Player);

	m_WADLoader.SetWADFilePath(GetWADFileName());
	m_WADLoader.LoadWAD();

	m_WADLoader.LoadMapData(m_pMap);

	return true;
}

bool DoomEngine::IsOver()
{
	return m_bIsOver;
}

int DoomEngine::GetRenderWidth()
{
	return m_iRenderWidth;
}

int DoomEngine::GetRenderHeight()
{
	return m_iRenderHeight;
}

int DoomEngine::GetTimePerFrame()
{
	return 1000/60;
}

void DoomEngine::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(m_Renderer);
	m_pMap->RenderAutoMap();
}

void DoomEngine::KeyPressed(SDL_Event &event)
{
	switch(event.key.keysym.sym)
	{
	case SDLK_UP:
		break;
	case SDLK_DOWN:
		break;
	case SDLK_RIGHT:
		break;
	case SDLK_LEFT:
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
	m_bIsOver = true;
}

void DoomEngine::Update()
{

}

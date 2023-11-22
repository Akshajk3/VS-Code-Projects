#include "VoomEngine.h"

VoomEngine::VoomEngine()
	: m_bIsOver(false), m_iRenderWidth(320), m_iRenderHeight(200)
{
	m_pMap = new Map("E1M1");
}

VoomEngine::~VoomEngine()
{
	delete m_pMap;
}

bool VoomEngine::Init()
{
	m_WADLoader.SetWADFilePath("wad/DOOM.WAD");
	m_WADLoader.LoadWAD();
	m_WADLoader.LoadMapData(m_pMap);
	return true;
}

std::string VoomEngine::GetWADFileName()
{
	return "wad/DOOM.WAD";
}

void VoomEngine::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(renderer);
	m_pMap->RenderAutoMap(renderer);
}

void VoomEngine::KeyPressed(SDL_Event& event)
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

	default:
		break;
	}
}

void VoomEngine::KeyReleased(SDL_Event& event)
{

}

void VoomEngine::Quit()
{
	m_bIsOver = true;
}

void VoomEngine::Update()
{

}

bool VoomEngine::isOver()
{
	return m_bIsOver;
}

int VoomEngine::GetRenderWidth()
{
	return m_iRenderWidth;
}

int VoomEngine::GetRenderHeight()
{
	return m_iRenderHeight;
}

std::string VoomEngine::GetName()
{
	return "Doom Vindel";
}

int VoomEngine::GetTimePerFrame()
{
	return 1000 / 60;
}
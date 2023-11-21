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
}
#pragma once

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "WADLoader.h"
#include "Map.h"
#include "Player.h"

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
	int m_iRenderWidth;
	int m_iRenderHeight;

	bool m_bIsOver;

	WADLoader m_WADLoader;
	Map* m_pMap;
	Player* m_Player;
	SDL_Renderer* m_Renderer;
};

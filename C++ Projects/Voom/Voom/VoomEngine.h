#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "WADLoader.h"

class VoomEngine
{
public:
	VoomEngine();
	~VoomEngine();

	virtual void Render(SDL_Renderer* renderer);
	virtual void KeyPressed(SDL_Event& event);
	virtual void KeyReleased(SDL_Event& event);
	virtual void Quit();
	virtual void Update();

	virtual bool isOver();
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
	Player* m_pPlayer;
};
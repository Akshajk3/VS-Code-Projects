#pragma once

#include "DoomEngine.h"

class Game
{
public:
	Game();
	virtual ~Game();

	void ProcessInput();
	void Render();
	void Update();
	void Delay();

	bool IsOver();
	bool Init();

protected:
	int m_iWindowWidth;
	int m_iWindowHeight;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	DoomEngine *m_DoomEngine;
};

#include "Game.h"

Game::Game()
	: m_iWindowWidth(1280), m_iWindowHeight(720)
{
	m_DoomEngine = new DoomEngine();
}

Game::~Game()
{
	delete m_DoomEngine;
	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);
	SDL_Quit();
}

bool Game::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL Failed to Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_Window = SDL_CreateWindow(m_DoomEngine->GetName().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_iWindowWidth, m_iWindowHeight, SDL_WINDOW_SHOWN);
	if (m_Window == nullptr)
	{
		std::cout << "Failed to Create Window Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_SOFTWARE);
	if (m_Renderer == nullptr)
	{
		std::cout << "Failed to Create Renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	if (!m_DoomEngine->Init())
	{
		std::cout << m_DoomEngine->GetName() << " Failed to Init" << std::endl;
		return false;
	}

	if (SDL_RenderSetLogicalSize(m_Renderer, m_DoomEngine->GetRenderWidth(), m_DoomEngine->GetRenderHeight()) != 0)
	{
		std::cout << "SDL Failed to set Logical Size Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Game::ProcessInput()
{
	SDL_Event event;

	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				m_DoomEngine->KeyPressed(event);
				break;
			
			case SDL_KEYUP:
				m_DoomEngine->KeyReleased(event);
				break;

			case SDL_QUIT:
				m_DoomEngine->Quit();
				break;
		}
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(m_Renderer);

	m_DoomEngine->Render(m_Renderer);

	SDL_RenderPresent(m_Renderer);
}

void Game::Update()
{
	m_DoomEngine->Update();
}

bool Game::IsOver()
{
	return m_DoomEngine->IsOver();
}

void Game::Delay()
{
	SDL_Delay(m_DoomEngine->GetTimePerFrame());
}

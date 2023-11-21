#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

bool Game::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL Failed to Init! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_Window = SDL_CreateWindow(m_VoomEngine->GetName().c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_iWindowWidth, m_iWindowHeight, SDL_WINDOW_SHOWN);
	if (m_Window == nullptr)
	{
		std::cout << "SDL Failed to create Window! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_SOFTWARE);
	if (m_Renderer == nullptr)
	{
		std::cout << "SDL Failed to create Renderer! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	if (!m_VoomEngine->Init())
	{
		std::cout << m_VoomEngine->GetName() << " Failed to init!" << std::endl;
		return false;
	}

	if (SDL_RenderSetLogicalSize(m_Renderer, m_VoomEngine->GetRenderWidth(), m_VoomEngine->GetRenderHeight()) != 0)
	{
		std::cout << "SDL failed to set logical size! SDL Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Game::ProcessInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			m_VoomEngine->KeyPressed(event);
			break;
		case SDL_KEYUP:
			m_VoomEngine->KeyReleased(event);
			break;

		case SDL_QUIT:
			m_VoomEngine->Quit();
			break;
		}
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 0xff);
	SDL_RenderClear(m_Renderer);

	m_VoomEngine->Render(m_Renderer);

	SDL_RenderPresent(m_Renderer);
}

void Game::Update()
{
	m_VoomEngine->Update();
}

bool Game::IsOver()
{
	return m_VoomEngine->isOver();
}

void Game::Delay()
{
	SDL_Delay(m_VoomEngine->GetTimePerFrame());
}
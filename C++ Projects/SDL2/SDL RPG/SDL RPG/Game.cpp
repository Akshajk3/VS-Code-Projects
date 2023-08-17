#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window == NULL)
		{
			std::cout << "Failed to create window. Error: " << SDL_GetError() << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL)
		{
			std::cout << "Failed to create renderer. Error: " << SDL_GetError() << std::endl;
		}
	}
	else
	{
		isRunning = false;
		std::cout << "SDL Failed to Init. Error: " << SDL_GetError() << std::endl;
	}

}

void Game::handleEvents()
{

}

void Game::update()
{

}

void Game::render()
{

}

void Game::clean()
{

}
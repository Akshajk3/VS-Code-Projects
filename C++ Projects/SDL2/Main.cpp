#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>


#define SCREEN_WIDTH = 1280
#define SCREEN_HEIGHT = 720

int main(int argc, char** argv)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL Failed to Init. Error: " << SDL_GetError() << std::endl;
	}

	SDL_Window *window = SDL_CreateWindow("Win Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
	if(!window)
	{
		std::cout << "Window failed to intialize. Error: " << SDL_GetError() << std::endl;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer)
	{
		std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
	}

	SDL_Surface *win_surface = SDL_GetWindowSurface(window);
	if(!win_surface)
	{
		std::cout << "how u have 3060ti and not even get win sur in this garbaj code. Error: " << SDL_GetError() << std::endl;
	}

	SDL_Event event;
	bool run = true;
	int green = 0;
	int red = 0;
	int blue = 0;

	while(run)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				run = false;
				SDL_Quit();
			}

			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				green = 0+(rand()%255);
				red = 0+(rand()%255);
				blue = 0+(rand()%255);
			}
		}
		
		SDL_SetRenderDrawColor(renderer, red, green, blue, 0);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}

	return 0;
}
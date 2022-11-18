#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

int main()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "BRUH UR PC BAD. Error: " << SDL_Error << std::endl;
	}

	SDL_Window *window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);

	if(!window)
	{
		std::cout << "Bro how u pc so bad that it cannot make window. Error: " << SDL_Error << std::endl;
	}

	SDL_Surface *window_surface = SDL_GetWindowSurface(window);

	if(!window_surface)
	{
		std::cout << "Bro u cant event get the window surface L. Error: " << SDL_Error << std::endl;
	}

	SDL_UpdateWindowSurface(window);

	bool gameRunning = true;
	SDL_Event event;
	
	while(gameRunning)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
		}
	}

	SDL_Quit();
	return 0;
	
}
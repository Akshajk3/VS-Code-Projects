#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "RenderWindow.cpp"

int main(int argc, char* args[])
{
	if(SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout <<"I want to die: SDL_ERROR:" << SDL_GetError() << std::endl;
	}
	
	if(!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "IMG_init has failed. ERROR: " << SDL_GetError() << std::endl;
	}

	RenderWindow window("Game v1.0", 1280, 720);

	bool run = true;

	SDL_Event event;

	while(run)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				run = false;
			}
		}
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}
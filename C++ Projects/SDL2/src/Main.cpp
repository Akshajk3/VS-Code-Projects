#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "RenderWindow.cpp"

int main(int argc, char* args[])
{
	if(SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout  << "Bruh L + ratio. Error: " << SDL_GetError() << std::endl;
	}

	if(!(IMG_Init(IMG_INIT_PNG)))
	{
		std::cout << "how is pc so bad cant even show image. Error: " << SDL_GetError << std::endl;
	}

	RenderWindow window("Game", 640, 480);
	return 0;
}
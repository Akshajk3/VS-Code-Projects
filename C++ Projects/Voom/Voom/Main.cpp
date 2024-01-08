#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "SDL Failed to Init. SDL Error: " << SDL_GetError << std::endl;
	}




	return 0;
}
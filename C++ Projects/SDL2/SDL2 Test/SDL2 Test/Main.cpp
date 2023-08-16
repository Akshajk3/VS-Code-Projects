#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL Failed to Init. SDL_ERROR: " << SDL_GetError() << std::endl;
		return -1;
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "SDL_Image Failed to Init. SDL_ERROR: " << SDL_GetError() << std::endl;
		return -1;
	}

	RenderWindow window("SDL Vindle Game", 1280, 720);

	SDL_Texture* grassTexture = window.loadTexture("gfx/ground_grass_1.png");

	std::vector<Entity> entities = {
		Entity(0, 150, grassTexture),
		Entity(30, 150, grassTexture),
		Entity(60, 150, grassTexture),
		Entity(90, 150, grassTexture),
		Entity(120, 150, grassTexture),
		Entity(150, 150, grassTexture),
		Entity(180, 150, grassTexture),
		Entity(210, 150, grassTexture),
		Entity(240, 150, grassTexture),
		Entity(270, 150, grassTexture),
		Entity(300, 150, grassTexture)
	};

	bool is_running = true;

	SDL_Event event;

	while (is_running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				is_running = false;
			}
		}
		
		window.clear();

		for (Entity& entity : entities)
		{
			window.render(entity);
		}

		window.display();
	}

	window.cleanUp();
	SDL_Quit();
	return 0;
}
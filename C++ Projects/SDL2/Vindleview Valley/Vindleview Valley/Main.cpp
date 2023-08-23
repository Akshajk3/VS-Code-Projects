#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector>
#include <string>

#include "RenderWindow.h"
#include "TextureManager.h"
#include "Entity.h"
#include "Animation.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL Failed to Init. SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "SDL Image Failed to Init. SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	RenderWindow window("Vindleview Valley", 800, 600);

	TextureManager textureManager;

	std::map<std::string, Animation> assets;

	std::map<std::string, std::string> assetPaths;

	assetPaths["idle"] = ("Assets/Characters/images/idle_down");

	//assets["player/idle_down"] = Animation(textureManager.loadTextures(assetPaths["idle"], window.renderer), 20, true);

	std::string playerPath = "Assets/Characters/images/walk_down";

	std::vector<SDL_Texture*> playerTex = textureManager.loadTextures(playerPath, window.renderer);

	Animation playerAnim(playerTex, 10, true);

	Entity player(0, 0, playerTex, playerAnim, "player");

	bool movement[4] = {false, false, false, false};

	bool isRunning = true;

	SDL_Event event;

	while (isRunning)
	{
		frameStart = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}

			if (event.type == SDL_KEYDOWN)
			{
				SDL_Keycode keyCode = event.key.keysym.sym;
				if (keyCode == SDLK_d)
				{
					movement[0] = true;
				}
				if (keyCode == SDLK_a)
				{
					movement[1] = true;
				}
				if (keyCode == SDLK_s)
				{
					movement[2] = true;
				}
				if (keyCode == SDLK_w)
				{
					movement[3] = true;
				}
			}
			if (event.type == SDL_KEYUP)
			{
				SDL_Keycode keyCode = event.key.keysym.sym;
				if (keyCode == SDLK_d)
				{
					movement[0] = false;
				}
				if (keyCode == SDLK_a)
				{
					movement[1] = false;
				}
				if (keyCode == SDLK_s)
				{
					movement[2] = false;
				}
				if (keyCode == SDLK_w)
				{
					movement[3] = false;
				}
			}
		}

		int move[2] = { movement[0] - movement[1], movement[2] - movement[3] };

		window.clear();
		player.update(move);
		window.render(player, 4);
		window.display();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	window.cleanUp();
	SDL_Quit();
	return 0;
}
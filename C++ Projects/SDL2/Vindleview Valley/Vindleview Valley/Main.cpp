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

	std::map<std::string, std::vector<SDL_Texture*>> assets;

	std::map<std::string, std::string> assetPaths;

	assetPaths["idle_down"] = ("Assets/Characters/images/idle_down");
	assetPaths["walk_down"] = ("Assets/Characters/images/walk_down");
	assetPaths["idle_left"] = ("Assets/Characters/images/idle_left");
	assetPaths["walk_left"] = ("Assets/Characters/images/walk_left");
	assetPaths["idle_right"] = ("Assets/Characters/images/idle_right");
	assetPaths["walk_right"] = ("Assets/Characters/images/walk_right");
	assetPaths["idle_up"] = ("Assets/Characters/images/idle_up");
	assetPaths["walk_up"] = ("Assets/Characters/images/walk_up");
	
	
	assets["idle_down"] = textureManager.loadTextures(assetPaths["idle_down"], window.renderer);
	assets["walk_down"] = textureManager.loadTextures(assetPaths["walk_down"], window.renderer);
	assets["idle_left"] = textureManager.loadTextures(assetPaths["idle_left"], window.renderer);
	assets["walk_left"] = textureManager.loadTextures(assetPaths["walk_left"], window.renderer);
	assets["idle_right"] = textureManager.loadTextures(assetPaths["idle_right"], window.renderer);
	assets["walk_right"] = textureManager.loadTextures(assetPaths["walk_right"], window.renderer);
	assets["idle_up"] = textureManager.loadTextures(assetPaths["idle_up"], window.renderer);
	assets["walk_up"] = textureManager.loadTextures(assetPaths["walk_up"], window.renderer);

	//assets["player/idle_down"] = Animation(textureManager.loadTextures(assetPaths["idle_down"], window.renderer), 20, true);

	std::string playerPath = "Assets/Characters/images/walk_down";

	std::vector<SDL_Texture*> playerTex = textureManager.loadTextures(assetPaths["idle_down"], window.renderer);

	Animation playerAnim(playerTex, 10, true);

	Entity player(0, 0, window.renderer, playerAnim, "player", assets);

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
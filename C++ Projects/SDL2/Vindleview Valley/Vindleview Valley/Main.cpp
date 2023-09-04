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
#include "Tilemap.h"
#include "Player.h"

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

	// Player Asset Paths
	assetPaths["idle_down"] = ("Assets/Characters/images/idle_down");
	assetPaths["walk_down"] = ("Assets/Characters/images/walk_down");
	assetPaths["hoe_down"] = ("Assets/Characters/images/hoe_down");
	assetPaths["idle_left"] = ("Assets/Characters/images/idle_left");
	assetPaths["walk_left"] = ("Assets/Characters/images/walk_left");
	assetPaths["idle_right"] = ("Assets/Characters/images/idle_right");
	assetPaths["walk_right"] = ("Assets/Characters/images/walk_right");
	assetPaths["idle_up"] = ("Assets/Characters/images/idle_up");
	assetPaths["walk_up"] = ("Assets/Characters/images/walk_up");

	// Entity Asset Paths
	assetPaths["cow_idle"] = ("Assets/Characters/images/cow/idle");
	assetPaths["chicken_idle"] = ("Assets/Characters/images/chicken/idle");
	
	// Tilemap Asset Paths
	assetPaths["grass"] = ("Assets/Tilesets/images/grass");
	assetPaths["fence"] = ("Assets/Tilesets/images/fence");
	
	assets["idle_down"] = textureManager.loadTextures(assetPaths["idle_down"], window.renderer);
	assets["walk_down"] = textureManager.loadTextures(assetPaths["walk_down"], window.renderer);
	assets["hoe_down"] = textureManager.loadTextures(assetPaths["hoe_down"], window.renderer);
	assets["idle_left"] = textureManager.loadTextures(assetPaths["idle_left"], window.renderer);
	assets["walk_left"] = textureManager.loadTextures(assetPaths["walk_left"], window.renderer);
	assets["idle_right"] = textureManager.loadTextures(assetPaths["idle_right"], window.renderer);
	assets["walk_right"] = textureManager.loadTextures(assetPaths["walk_right"], window.renderer);
	assets["idle_up"] = textureManager.loadTextures(assetPaths["idle_up"], window.renderer);
	assets["walk_up"] = textureManager.loadTextures(assetPaths["walk_up"], window.renderer);

	assets["cow_idle"] = textureManager.loadTextures(assetPaths["cow_idle"], window.renderer);
	assets["chicken_idle"] = textureManager.loadTextures(assetPaths["chicken_idle"], window.renderer);

	assets["grass"] = textureManager.loadTextures(assetPaths["grass"], window.renderer);
	assets["fence"] = textureManager.loadTextures(assetPaths["fence"], window.renderer);
	
	SDL_Texture* background = textureManager.loadTexture("Assets/Tilesets/test_background.png", window.renderer);

	//SDL_Texture* grass = textureManager.loadTexture("Assets/Tilesets/images/grass/Grass_0.png", window.renderer);

	SDL_Texture* cursorTexture = textureManager.loadTexture("Assets/Mouse_sprites/Cursor_1.png", window.renderer);

	SDL_ShowCursor(SDL_DISABLE);

	//assets["player/idle_down"] = Animation(textureManager.loadTextures(assetPaths["idle_down"], window.renderer), 20, true);

	std::string playerPath = "Assets/Characters/images/walk_down";

	Animation playerAnim(assets["idle_down"], 10, true);

	Animation cowAnim(assets["cow"], 10, true);

	Animation chickenAnim(assets["chicken_idle"], 10,  true);

	Player player(0, 0, window.renderer, playerAnim, assets);
	
	Entity cow(10, 10, window.renderer, cowAnim, "cow", assets);
	Entity chicken(100, 100, window.renderer, chickenAnim, "chicken", assets);

	Tilemap tilemap(assets);

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
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					//player.setAction("hoe");
				}
			}
		}

		int move[2] = { movement[0] - movement[1], movement[2] - movement[3] };

		window.clear();
		player.update(move);
		cow.update();
		tilemap.DrawMap(window.renderer);
		//SDL_RenderCopy(window.renderer, cowTex[1], nullptr, nullptr);
		window.render(cow, 4);
		window.render(chicken, 2);
		window.render(player, 4);

		int mouseX;
		int	mouseY;

		SDL_GetMouseState(&mouseX, &mouseY);

		SDL_Rect cursorRect = { mouseX, mouseY, 32, 32 };
		SDL_RenderCopy(window.renderer, cursorTexture, nullptr, &cursorRect);

		window.display();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	window.cleanUp();
	IMG_Quit();
	SDL_Quit();
	return 0;
}

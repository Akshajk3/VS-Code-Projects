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
#include "Plant.h"

int grass[20][25] = {
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
};

int plants[20][25] = {
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
    { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
};

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
	assetPaths["axe_down"] = ("Assets/Characters/images/axe_down");
	assetPaths["water_down"] = ("Assets/Characters/images/water_down");
	assetPaths["idle_left"] = ("Assets/Characters/images/idle_left");
	assetPaths["walk_left"] = ("Assets/Characters/images/walk_left");
	assetPaths["hoe_left"] = ("Assets/Characters/images/hoe_left");
	assetPaths["axe_left"] = ("Assets/Characters/images/axe_left");
	assetPaths["water_left"] = ("Assets/Characters/images/water_left");
	assetPaths["idle_right"] = ("Assets/Characters/images/idle_right");
	assetPaths["walk_right"] = ("Assets/Characters/images/walk_right");
	assetPaths["hoe_right"] = ("Assets/Characters/images/hoe_right");
	assetPaths["axe_right"] = ("Assets/Characters/images/axe_right");
	assetPaths["water_right"] = ("Assets/Characters/images/water_right");
	assetPaths["idle_up"] = ("Assets/Characters/images/idle_up");
	assetPaths["walk_up"] = ("Assets/Characters/images/walk_up");
	assetPaths["hoe_up"] = ("Assets/Characters/images/hoe_up");
	assetPaths["axe_up"] = ("Assets/Characters/images/axe_up");
	assetPaths["water_up"] = ("Assets/Characters/images/water_up");

// Entity Asset Paths
	assetPaths["cow_idle"] = ("Assets/Characters/images/cow/idle");
	assetPaths["chicken_idle"] = ("Assets/Characters/images/chicken/idle");
	
// Tilemap Asset Paths
	assetPaths["grass"] = ("Assets/Tilesets/images/grass");
	assetPaths["fence"] = ("Assets/Tilesets/images/fence");
	assetPaths["till"] = ("Assets/Tilesets/images/till");

// UI Asset Paths
	assetPaths["hoe"] = ("Assets/Objects/images/Basic tools and meterials_2.png");
	assetPaths["axe"] = ("Assets/Objects/images/Basic tools and meterials_1.png");
	assetPaths["water"] = ("Assets/Objects/images/Basic tools and meterials_0.png");
    assetPaths["wheatBag"] = ("Assets/Objects/images/wheat/00.png");
    
// Plant Asests Paths
    assetPaths["wheat"] = ("Assets/Objects/images/wheat");
	
// Player Assets
	assets["idle_down"] = textureManager.loadTextures(assetPaths["idle_down"], window.renderer);
	assets["walk_down"] = textureManager.loadTextures(assetPaths["walk_down"], window.renderer);
	assets["hoe_down"] = textureManager.loadTextures(assetPaths["hoe_down"], window.renderer);
	assets["axe_down"] = textureManager.loadTextures(assetPaths["axe_down"], window.renderer);
	assets["water_down"] = textureManager.loadTextures(assetPaths["water_down"], window.renderer);
	assets["idle_left"] = textureManager.loadTextures(assetPaths["idle_left"], window.renderer);
	assets["walk_left"] = textureManager.loadTextures(assetPaths["walk_left"], window.renderer);
	assets["hoe_left"] = textureManager.loadTextures(assetPaths["hoe_left"], window.renderer);
	assets["axe_left"] = textureManager.loadTextures(assetPaths["axe_left"], window.renderer);
	assets["water_left"] = textureManager.loadTextures(assetPaths["water_left"], window.renderer);
	assets["idle_right"] = textureManager.loadTextures(assetPaths["idle_right"], window.renderer);
	assets["walk_right"] = textureManager.loadTextures(assetPaths["walk_right"], window.renderer);
	assets["hoe_right"] = textureManager.loadTextures(assetPaths["hoe_right"], window.renderer);
	assets["axe_right"] = textureManager.loadTextures(assetPaths["axe_right"], window.renderer);
	assets["water_right"] = textureManager.loadTextures(assetPaths["water_right"], window.renderer);
	assets["idle_up"] = textureManager.loadTextures(assetPaths["idle_up"], window.renderer);
	assets["walk_up"] = textureManager.loadTextures(assetPaths["walk_up"], window.renderer);
	assets["hoe_up"] = textureManager.loadTextures(assetPaths["hoe_up"], window.renderer);
	assets["axe_up"] = textureManager.loadTextures(assetPaths["axe_up"], window.renderer);
	assets["water_up"] = textureManager.loadTextures(assetPaths["water_up"], window.renderer);

// Entity Assets
	assets["cow_idle"] = textureManager.loadTextures(assetPaths["cow_idle"], window.renderer);
	assets["chicken_idle"] = textureManager.loadTextures(assetPaths["chicken_idle"], window.renderer);

// Tilemap Assets
	assets["grass"] = textureManager.loadTextures(assetPaths["grass"], window.renderer);
	assets["fence"] = textureManager.loadTextures(assetPaths["fence"], window.renderer);
	assets["till"] = textureManager.loadTextures(assetPaths["till"], window.renderer);

// UI Assets
	SDL_Texture* cursorTexture = textureManager.loadTexture("Assets/Mouse_sprites/Cursor_1.png", window.renderer);
	SDL_Texture* hoe_icon = textureManager.loadTexture(assetPaths["hoe"].c_str(), window.renderer);
	SDL_Texture* axe_icon = textureManager.loadTexture(assetPaths["axe"].c_str(), window.renderer);
	SDL_Texture* water_icon = textureManager.loadTexture(assetPaths["water"].c_str(), window.renderer);
    SDL_Texture* wheat_icon = textureManager.loadTexture(assetPaths["wheatBag"].c_str(), window.renderer);

// Plant Assets
    assets["wheat"] = textureManager.loadTextures(assetPaths["wheat"], window.renderer);

	SDL_ShowCursor(SDL_DISABLE);

	Player player(0, 0, window.renderer, assets);
	
	Entity cow(100, 10, window.renderer, "cow", assets);
	Entity chicken(100, 100, window.renderer, "chicken", assets);

	Tilemap backGroundTilemap(assets);
    backGroundTilemap.LoadMap(grass);
    
    Tilemap plantTiles(assets);
    plantTiles.LoadMap(plants);
    bool plant = false;
    
    std::vector<Plant> Plants;

	bool movement[4] = {false, false, false, false};

	int mouseX;
	int	mouseY;

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
				if (keyCode == SDLK_1)
				{
					player.setTool("hoe");
				}
				if (keyCode == SDLK_2)
				{
					player.setTool("axe");
				}
				if (keyCode == SDLK_3)
				{
					player.setTool("water");
				}
                if (keyCode == SDLK_4)
                {
                    player.setTool("wheat");
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
					if (player.getTimer() == 0)
					{
						player.act();

						if(player.getTool() == "hoe")
							backGroundTilemap.setTile(mouseX, mouseY, 2);
                        if(player.getTool() == "wheat" && backGroundTilemap.getTile(mouseX, mouseY) == 2)
                        {
                            plantTiles.setTile(mouseX, mouseY, 3);
                            Plants.push_back(Plant(mouseX, mouseY, "wheat", 10, plantTiles));
                            plant = true;
                        }
					}
				}
			}
		}

		int move[2] = { movement[0] - movement[1], movement[2] - movement[3] };

		//std::cout << "Player X: " << player.getX() << std::endl;
		//std::cout << "Player Y: " << player.getY() << std::endl;

		window.clear();
		player.update(move);
		cow.update();
		backGroundTilemap.DrawMap(window.renderer);
        plantTiles.DrawMap(window.renderer);
		window.render(cow, 4);
		window.render(chicken, 2);
		window.render(player, 4);
        
        /*
        for (Plant plant : Plants)
            plant.update();
         */
        if (plant == true)
            Plants[0].update();
         
		SDL_GetMouseState(&mouseX, &mouseY);

		SDL_Rect toolRect = { 0, 0, 64, 64 };

		if (player.getTool() == "hoe")
		{
			SDL_RenderCopy(window.renderer, hoe_icon, nullptr, &toolRect);	
		}
		if (player.getTool() == "axe")
		{
			SDL_RenderCopy(window.renderer, axe_icon, nullptr, &toolRect);
		}
		if (player.getTool() == "water")
		{
			SDL_RenderCopy(window.renderer, water_icon, nullptr, &toolRect);
		}
        if(player.getTool() == "wheat")
        {
            SDL_RenderCopy(window.renderer, wheat_icon, nullptr, &toolRect);
        }

		SDL_Rect cursorRect = { mouseX, mouseY, 32, 32 };
		SDL_RenderCopy(window.renderer, cursorTexture, nullptr, &cursorRect);

		//std::cout << tilemap.getTile(mouseX, mouseY);

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

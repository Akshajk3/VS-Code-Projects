#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Entity.h"

class RenderWindow
{
public:
	RenderWindow(const char* windowName, int width, int height);
	SDL_Texture* loadTexture(const char* filePath);
	void cleanUp();
	void clear();
	void render(Entity& entity, int entityScale, int cameraX, int cameraY, bool player = false, int windowWidth = 0, int windowHeight = 0);
	void display();

	SDL_Renderer* renderer;
private:
	SDL_Window* window;
	int currentFrame = 0;
};

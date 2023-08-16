#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Entity.h"

class RenderWindow
{
public:
	RenderWindow(const char* windowName, int width, int height);
	SDL_Texture* loadTexture(const char* filePath);
	void cleanUp();
	void clear();
	void render(Entity& entity);
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
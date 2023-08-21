#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class TextureManager
{
public:
	TextureManager(SDL_Renderer* ren);
	SDL_Texture* loadTexture(const char* filename);
private:
	SDL_Renderer* renderer;
};
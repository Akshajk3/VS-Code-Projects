#include "TextureManager.h"

TextureManager::TextureManager(SDL_Renderer* ren) : renderer(ren) {}

SDL_Texture* TextureManager::loadTexture(const char* filename)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filename);
	
	if (texture == NULL)
	{
		std::cout << "Failed to Load Texture. SDL_Error: " << SDL_GetError() << std::endl;
	}

	return texture;
}


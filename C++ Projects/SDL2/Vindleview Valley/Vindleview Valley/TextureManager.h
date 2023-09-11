#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#if __cplusplus == 201103L
#include <experimental/filesystem>
#else
#include <filesystem>
#endif
#include <algorithm>
#include <string>

class TextureManager
{
public:
	TextureManager();
	SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer);
	std::vector<SDL_Texture*> loadTextures(std::string& filePath, SDL_Renderer* renderer);
};
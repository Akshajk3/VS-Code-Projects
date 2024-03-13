#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <filesystem>

class TextureManager
{
public:
    TextureManager();
    SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer);
    std::vector<SDL_Texture*> loadTextures(std::string& filepath, SDL_Renderer* renderer);
};

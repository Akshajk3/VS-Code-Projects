#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#if __cplusplus == 201103L
#include <experimental/filesystem
#else
#include <filesystem>
#include <algorithm>
#include <string>

class TextureManager
{
public:
    TextureManager();
    SDL_Texture* loadTexture(const char*)
};

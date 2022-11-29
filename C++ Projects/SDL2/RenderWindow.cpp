#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <math.h>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        std::cout << "how u so bad u can even get window to open absolute trash. Error: " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);
    
    if(texture == NULL)
    {
        std::cout << "Naw how are u so bad at coding that u are trying to load a image that does not exist. Error: " << SDL_GetError() << std::endl;
    }

    return texture;
}

void RenderWindow::CleanUp()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(SDL_Texture* p_tex)
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = 800;
    src.h = 300;

    SDL_Rect dst;
    dst.x = 0;
    dst.y = 600-dst.h;
    dst.w = 800;
    dst.h = 300;

    SDL_RenderCopy(renderer, p_tex, &src, &dst);
    SDL_SetRenderDrawColor(renderer, 0, 181, 226, 0);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}
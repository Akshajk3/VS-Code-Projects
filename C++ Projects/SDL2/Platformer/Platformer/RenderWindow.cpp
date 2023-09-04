#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* windowName, int width, int height)
{
    window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Failed to Create Window. Error: " << SDL_GetError() << std::endl;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cout << "Failed to Create Renderer. Error: " << SDL_GetError() << std::endl;
    }
}

void RenderWindow::cleanUp()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render()
{
    
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}

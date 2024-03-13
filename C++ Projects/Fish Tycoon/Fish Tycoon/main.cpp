#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

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
    
    SDL_Window* window = SDL_CreateWindow("Fish Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Failed to Create SDL Window. SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        IMG_Quit();
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        std::cout << "Failed to Create SDL Renderer. SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        IMG_Quit();
    }
    
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    
    Uint32 frameStart;
    int frameTime;
    
    bool running = true;
    SDL_Event event;
    while (running)
    {
        frameStart = SDL_GetTicks();
        
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }
        
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}

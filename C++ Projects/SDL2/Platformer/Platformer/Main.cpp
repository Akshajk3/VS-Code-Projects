#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.h"

int main(int argc, const char * argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::cout << "SDL Failed to Init. Error: " << SDL_GetError() << std::endl;
    }
    if (!IMG_Init(IMG_INIT_PNG))
    {
        std::cout << "SDL Image Failed to Init. Error: " << SDL_GetError() << std::endl;
    }
    
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    
    Uint32 frameStart;
    int frameTime;
    
    RenderWindow window("Vindel Game", 800, 600);
    
    bool isRunning = true;
    
    SDL_Event event;
    
    while (isRunning)
    {
        frameStart = SDL_GetTicks();
        
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }
        
        window.clear();
        window.render();
        window.display();
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    
    window.cleanUp();
    IMG_Quit();
    SDL_Quit();
    return 0;
}

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "RenderWindow.hpp"
#include "RenderWindow.cpp"

#include "Entity.hpp"
#include "Entity.cpp"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argv, char* args[])
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL failed to Init. Error: " << SDL_GetError() << std::endl;
    }

    if(!(IMG_Init(IMG_INIT_PNG)))
    {
        std::cout << "SDL Image failed to Init. Error: " << SDL_GetError() << std::endl;
    }
 

    RenderWindow window("Test", SCREEN_WIDTH, SCREEN_HEIGHT);

    SDL_Texture* grassTexture = window.loadTexture("gfx/ground_grass.png");

    bool run = true;
    SDL_Event event;

    while(run)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                run = false;
            }
        }

        window.clear();
        window.render(grassTexture);
        window.display();
    }

    window.CleanUp();
    SDL_Quit();

    return 0;
}
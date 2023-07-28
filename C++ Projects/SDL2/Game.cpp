#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"


GameObject* player;

Game::Game()
{

}

Game::~Game()
{

}

void Game::init(const char* windowName, int xpos, int ypos, int windowWidth, int windowHeight, bool fullscreen)
{
    int flags = 0;
    if(fullscreen == true)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystems Initilized..." << std::endl;

        window = SDL_CreateWindow(windowName, xpos, ypos, windowWidth, windowHeight, flags);
        if(window)
        {
            std::cout << "Window Created..." << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer Created..." << std::endl;
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    player = new GameObject("gfx/pixilart-drawing.png", renderer);
}
void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    
    default:
        break;
    }
}
void Game::update()
{
    cnt++;
    destR.h = 64;
    destR.w = 64;
    destR.x = cnt;

    std::cout << cnt << std::endl;
}
void Game::render()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, playerTex, NULL, &destR);
    SDL_RenderPresent(renderer);
}
void Game::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}
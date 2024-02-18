#include "Game.h"

Game::Game()
    : WindowWidth(1280), WindowHeight(800)
{
    doomEngine = new DoomEngine();
}

Game::~Game()
{
    delete doomEngine;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Game::Init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "Failed to Init SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    
    window = SDL_CreateWindow("Voon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
    if(window == nullptr)
    {
        std::cout << "Failed to Create SDL Window: " << SDL_GetError() << std::endl;
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if(renderer == nullptr)
    {
        std::cout << "Failed to Create SDL Renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    if(!doomEngine->Init())
    {
        std::cout << "Failed to Init Doom Engine: " << doomEngine->GetName() << std::endl;
        return false;
    }
    
    if(SDL_RenderSetLogicalSize(renderer, doomEngine->GetRenderWidth(), doomEngine->GetRenderHeight()) != 0)
    {
        std::cout << "Failed to set logical size: " << SDL_GetError() << std::endl;
        return false;
    }
    
    return true;
}

void Game::HandelInput()
{
    SDL_Event event;
    
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                doomEngine->KeyPressed(event);
                break;
            case SDL_KEYUP:
                doomEngine->KeyReleased(event);
                break;
            
            case SDL_QUIT:
                doomEngine->Quit();
                break;
        }
    }
}

void Game::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xff);
    SDL_RenderClear(renderer);
    
    doomEngine->Render(renderer);
    SDL_RenderPresent(renderer);
}

void Game::Update()
{
    doomEngine->Update();
}

bool Game::IsOver()
{
    return doomEngine->IsOver();
}

void Game::Delay()
{
    SDL_Delay(doomEngine->GetTimePerFrame());
}

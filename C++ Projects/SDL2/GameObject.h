#pragma once

#include "Game.h"

class GameObject
{
private:
    int xpos;
    int ypos;

    SDL_Texture* objectTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;

public:
    GameObject(const char* texturesheet, SDL_Renderer* ren);
    ~GameObject();

    void Update();
    void Render();
};
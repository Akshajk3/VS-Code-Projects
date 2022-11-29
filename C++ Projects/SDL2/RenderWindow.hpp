#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class RenderWindow
{
    public:
        RenderWindow(const char* p_title, int p_h, int p_w);
        SDL_Texture* loadTexture(const char* p_filePath);
        void CleanUp();
        void clear();
        void render(SDL_Texture* p_tex);
        void display();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};
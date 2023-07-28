#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Game
{
private:
    int cnt = 0;
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    Game();
    ~Game();

    void init(const char* windowName, int xpos, int ypos, int windowWidth, int windowHeight, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running()
    {
        return isRunning;
    }
};

#endif
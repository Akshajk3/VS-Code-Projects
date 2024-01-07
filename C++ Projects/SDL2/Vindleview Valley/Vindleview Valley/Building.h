#pragma once

#include <SDL2/SDL.h>

class Building
{
public:
    Building(int p_x, int p_y, SDL_Texture* tex, SDL_Renderer* ren, bool place = false, bool transparent = false);
    void update(int mouseX, int mouseY);
    void render(int cameraX, int cameraY);
    bool isPlaced();
    //void Place();
    
private:
    int x, y;
    SDL_Texture* texture;
    SDL_Renderer* renderer;
    SDL_Rect src, dest;
    bool placed = false;
};

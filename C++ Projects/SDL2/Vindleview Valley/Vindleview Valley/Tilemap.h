#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include <vector>

class Tilemap
{
public:
    Tilemap(std::map<std::string, std::vector<SDL_Texture*>> sprites, int p_row, int p_col);
    ~Tilemap();

    void setTile(float p_x, float p_y, int tile);
    int getTile(float p_x, float p_y);

    void LoadMap(int arr[40][50]);
    void DrawMap(SDL_Renderer* ren, int mouseX, int mouseY);

private:
    SDL_Rect src, dest;
    std::map<std::string, std::vector<SDL_Texture*>> assets;

    int rows, cols;
    
    int** map;
};

#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include <vector>

class Tilemap
{
public:
    Tilemap(SDL_Texture* grassTex1);

    void LoadMap(int arr[20][25]);
    void DrawMap(SDL_Renderer* ren);

private:
    SDL_Rect src, dest;
    //std::map<std::string, std::vector<SDL_Texture*>> assets;

    SDL_Texture* grass1;

    int map[20][25];
};
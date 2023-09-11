#include "Tilemap.h"
#include "TextureManager.h"

Tilemap::Tilemap(std::map<std::string, std::vector<SDL_Texture*>> sprites)
    : assets(sprites)
{
    src.x = 0;
    src.y = 0;
    src.w = dest.w = 32;
    src.h = dest.h = 32;

    dest.x = 0;
    dest.y = 0;
}

void Tilemap::DrawMap(SDL_Renderer* ren)
{
    int type = 0;

    for (int row = 0; row < 20; row++)
    {
        for (int col = 0; col < 25; col++)
        {
            type = map[row][col];

            dest.x = col * 32;
            dest.y = row * 32;

            if (type == 1)
            {
                SDL_RenderCopy(ren, assets["grass"][0], &src, &dest);
            }
            if (type == 2)
            {
                SDL_RenderCopy(ren, assets["till"][0], &src, &dest);
            }
            if (type == 3)
            {
                SDL_RenderCopy(ren, assets["wheat"][1], &src, &dest);
            }
        }
    }
}

void Tilemap::LoadMap(int arr[20][25])
{
    for (int row = 0; row < 20; row++)
    {
        for (int col = 0; col < 25; col++)
        {
            map[row][col] = arr[row][col];
        }
    }
}

void Tilemap::setTile(float p_x, float p_y, int tile)
{
    int row = int(p_y / 32);
    int col = int(p_x / 32);

    row = std::min(row, 20);
    col = std::min(col, 25);

    map[row][col] = tile;
}

int Tilemap::getTile(float p_x, float p_y)
{
    int row = int(p_y / 32);
    int col = int(p_x / 32);
    
    row = std::min(row, 20);
    col = std::min(col, 25);
    
    return map[row][col];
}

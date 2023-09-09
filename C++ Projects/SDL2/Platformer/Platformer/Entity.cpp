#include "Entity.h"

#include <cmath>
#include <vector>

std::string BASE_IMG_PATH = "Assets/Characters/images";

Entity::Entity(float p_x, float p_y, SDL_Renderer* ren, std::string type, std::map<std::string, std::vector<SDL_Texture*>> assets)
    : x(p_x), y(p_y), renderer(ren), type(type), asset(assets), animation(assets["idle"])
{
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 16;
    currentFrame.h = 16;
}

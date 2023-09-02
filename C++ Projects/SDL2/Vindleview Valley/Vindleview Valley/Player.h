#pragma once

#include "Entity.h"

#include <cmath>

class Player : public Entity
{
public:
	Player(float p_x, float p_y, SDL_Renderer* ren, Animation anim, std::map<std::string, std::vector<SDL_Texture*>> asset);

	void update(int movement[2]);
};
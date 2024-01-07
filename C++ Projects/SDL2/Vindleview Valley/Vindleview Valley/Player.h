#pragma once

#include "Entity.h"

#include <iostream>
#include <cmath>
#include <algorithm>

class Player : public Entity
{
public:
	Player(float p_x, float p_y, SDL_Renderer* ren, std::map<std::string, std::vector<SDL_Texture*>> asset);
	void update(int movement[2]);
	void act();
	void setTool(std::string newTool);
	std::string getTool();
	int getTimer();

private:
	int actionTimer = 0;
	std::string tool = "hoe";
};
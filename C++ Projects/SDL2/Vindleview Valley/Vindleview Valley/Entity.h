#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "Animation.h"

class Entity
{
public:
	Entity(float p_x, float p_y, std::vector<SDL_Texture*> tex, Animation anim, std::string type);
	float getX();
	float getY();
	std::vector<SDL_Texture*> getTextures();
	SDL_Rect getCurrentFrame();
	Animation getAnimation();
	void setAction(std::string act);
	void getAnimation();

	void update(int movement[2]);
	float* normalize(float movement[2]);

private:
	float x, y;
	SDL_Rect currentFrame;
	std::vector<SDL_Texture*> textures;
	Animation animation;
	int frame = 0;
	std::string action;
	std::string type;
	//int velocity[4] = { 0, 0 };
};
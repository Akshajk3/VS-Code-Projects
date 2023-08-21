#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

class Entity
{
public:
	Entity(float p_x, float p_y, std::vector<SDL_Texture*> tex);
	float getX();
	float getY();
	std::vector<SDL_Texture*> getTextures();
	SDL_Rect getCurrentFrame();

	void update(int movement[2]);
	float* normalize(float movement[2]);
private:
	float x, y;
	SDL_Rect currentFrame;
	std::vector<SDL_Texture*> textures;

	//int velocity[4] = { 0, 0 };
};
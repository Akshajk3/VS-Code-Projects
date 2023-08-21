#pragma once

#include <SDL2/SDL.h>
#include <iostream>

class Entity
{
public:
	Entity(float p_x, float p_y, SDL_Texture* tex);
	float getX();
	float getY();
	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame();

	void update(int movement[2]);
	float* normalize(float movement[2]);
private:
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* texture;

	//int velocity[4] = { 0, 0 };
};
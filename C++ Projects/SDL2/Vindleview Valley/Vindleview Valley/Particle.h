#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "Animation.h"

class Particle
{
public:
	Particle(float p_x, float p_y, int scale, std::vector<SDL_Texture*> sprites, SDL_Renderer* ren);
	void update();
	void render(int cameraX, int cameraY);
	
	bool kill = false;

private:
	float x, y;
	std::vector<SDL_Texture*> textures;
	SDL_Renderer* renderer;
	Animation anim;

	SDL_Rect dest, src;
};
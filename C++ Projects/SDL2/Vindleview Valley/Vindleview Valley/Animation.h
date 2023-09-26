#pragma once

#include <SDL2/SDL.h>
#include <algorithm>
#include <vector>
#include <iostream>

class Animation
{
public:
	Animation(std::vector<SDL_Texture*> textures, int img_dur = 5, bool loop = true);
	void update();
	SDL_Texture* img();
	bool done = false;
private:
	std::vector<SDL_Texture*> images;
	int image_duration;
	bool loop;
	int frame = 0;
};
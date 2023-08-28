#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>

#include "Animation.h"
#include "TextureManager.h"

class Entity
{
public:
	Entity(float p_x, float p_y, SDL_Renderer* ren, Animation anim, std::string type, std::map<std::string, std::vector<SDL_Texture*>> assets);
	float getX();
	float getY();
	//std::vector<SDL_Texture*> getTextures();
	SDL_Rect getCurrentFrame();
	Animation getAnimation();
	void setAction(std::string act);
	//void getAnimation();

	void update(int movement[2]);
	//float* normalize(float movement[2]);

private:
	float x, y;
	SDL_Rect currentFrame;
	Animation animation;
	int frame = 0;
	std::string action;
	std::string type;
	std::string direction = "down";
	std::string oldDirection = direction;
	SDL_Renderer* renderer;
	std::map<std::string, std::vector<SDL_Texture*>> asset;
	bool canMove = true;
	//int velocity[4] = { 0, 0 };
};
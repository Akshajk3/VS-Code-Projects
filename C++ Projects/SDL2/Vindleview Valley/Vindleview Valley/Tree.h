#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include <string>

class Tree
{
public:
	Tree(int p_x, int p_y, int type, std::vector<SDL_Texture*> sprites, SDL_Renderer* ren);

	void render(int cameraX, int cameraY);
	void takeDamage();
	void die();
	int getX();
	int getY();
	bool checkClick(SDL_Rect mouseRect);

	bool dead = false;

private:
	int health = 3;
	std::vector<SDL_Texture*> assets;
	int x, y;
	int type;
	SDL_Rect src, dest;
	SDL_Renderer* renderer;
};

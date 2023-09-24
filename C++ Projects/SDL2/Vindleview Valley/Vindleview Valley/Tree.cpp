#include "Tree.h"

Tree::Tree(int p_x, int p_y, int p_type, std::vector<SDL_Texture*> sprites, SDL_Renderer* ren)
	: x(p_x), y(p_y), type(p_type), assets(sprites), renderer(ren)
{
	src.x = 0;
	src.y = 0;

	src.w = dest.w = 14 * 5;
	src.h = dest.h = 29 * 5;
	dest.x = x;
	dest.y = y;
}

void Tree::render()
{
	SDL_RenderCopy(renderer, assets[type], &src, &dest);
}

bool Tree::checkClick(SDL_Rect mouseRect)
{
	return (mouseRect.x < dest.x + dest.w &&
		mouseRect.x + mouseRect.w > dest.x &&
		mouseRect.y < dest.y + dest.h &&
		mouseRect.y + mouseRect.h > dest.y);

}

void Tree::die()
{
	type = 2;
	src.w = dest.w = 8 * 5;
	src.h = dest.h = 10 * 5;
	src.x = dest.x;
	src.y = 0;
}
#include "Entity.h"

Entity::Entity(float p_x, float p_y, SDL_Texture* texture)
	:x(p_x), y(p_y), tex(texture)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
}

float Entity::getX()
{
	return x;
}

float Entity::getY()
{
	return y;
}

SDL_Texture* Entity::getTexture()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}
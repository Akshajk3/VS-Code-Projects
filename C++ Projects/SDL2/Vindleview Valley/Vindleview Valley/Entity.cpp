#include "Entity.h"

#include <cmath>
#include <vector>

std::string BASE_IMG_PATH = "Assets/Characters/images";

Entity::Entity(float p_x, float p_y, SDL_Renderer* ren, std::string type, std::map<std::string, std::vector<SDL_Texture*>> assets)
: x(p_x), y(p_y), renderer(ren), type(type), asset(assets), animation(Animation(assets["idle"]))
{
	if (type == "player")
	{
		currentFrame.x = 0;
		currentFrame.y = 0;
		currentFrame.w = 48;
		currentFrame.h = 48;
	}
	else
	{
		currentFrame.x = 0;
		currentFrame.y = 0;
		currentFrame.w = 32;
		currentFrame.h = 32;
	}
    

	setAction("idle");
}

float Entity::getX()
{
	return x;
}

float Entity::getY()
{
	return y;
}

/*
std::vector<SDL_Texture*> Entity::getTextures()
{
	return textures;
}
*/

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

Animation Entity::getAnimation()
{
	return animation;
}

void Entity::setAction(std::string act)
{
	if (act != action || oldDirection != direction)
	{
		action = act;

		std::string assetPath;
		int animSpeed = 40;

		if (type == "player")
		{
			assetPath = action + "_" + direction;
			if (action == "walk")
				animSpeed = 10;
			if (action == "idle")
				animSpeed = 30;
		}
		else
		{
			assetPath = type + "_" + action;
		}
		animation = Animation(asset[assetPath], animSpeed, true);

		oldDirection = direction;
	}
}

void Entity::update()
{
	animation.update();
}

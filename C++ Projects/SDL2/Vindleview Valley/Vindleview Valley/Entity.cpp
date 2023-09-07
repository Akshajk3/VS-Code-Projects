#include "Entity.h"

#include <cmath>
#include <vector>

std::string BASE_IMG_PATH = "Assets/Characters/images";

Entity::Entity(float p_x, float p_y, SDL_Renderer* ren, Animation anim, std::string type, std::map<std::string, std::vector<SDL_Texture*>> assets)
	: x(p_x), y(p_y), renderer(ren), animation(anim), type(type), asset(assets)
{
	if (type == "player")
	{
		currentFrame.x = 0;
		currentFrame.y = 0;
		currentFrame.w = 16;
		currentFrame.h = 16;
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
	Uint32 lastUpdateTime = SDL_GetTicks();
	Uint32 animationSpeed;
	
	if(act == "hoe")
		animationSpeed = 100;
	else
	{
		animationSpeed = 0;
	}

	Uint32 currentTime = SDL_GetTicks();

	if(currentTime - lastUpdateTime >= animationSpeed)
	{
		if (act != action || oldDirection != direction)
		{
			action = act;

			std::string assetPath;
			int animSpeed = 20;

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
}

void Entity::update()
{
	animation.update();
}
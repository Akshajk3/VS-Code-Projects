#include "Entity.h"

#include <cmath>
#include <vector>

std::string BASE_IMG_PATH = "Assets/Characters/images";

Entity::Entity(float p_x, float p_y, SDL_Renderer* ren, Animation anim, std::string type, std::map<std::string, std::vector<SDL_Texture*>> assets)
	: x(p_x), y(p_y), renderer(ren), animation(anim), type(type), asset(assets)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 16;
	currentFrame.h = 16;

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

		if (type == "player")
			assetPath = action + "_" + direction;
		else
			assetPath = type + "_" + action;

		int animSpeed = 10;

		if (action == "walk")
			animSpeed = 10;
		if (action == "idle")
			animSpeed = 30;

		animation = Animation(asset[assetPath], animSpeed, true);

		oldDirection = direction;
	}

}

void Entity::update(int movement[2])
{
	if(type == "player")
	{
		float frame_movement[2] = { movement[0], movement[1] };

		//float* normalizedFrameMovement = normalize(frame_movement);

		float magnitude = sqrt(frame_movement[0] * frame_movement[0] + frame_movement[1] * frame_movement[1]);
		if (magnitude > 0)
		{
			frame_movement[0] /= magnitude;
			frame_movement[1] /= magnitude;
		}

		if (frame_movement[0] != 0 || frame_movement[1] != 0)
		{
			if (frame_movement[1] < 0)
				//setAction("walk_up");
				direction = "up";
			else if (frame_movement[1] > 0)
				//setAction("walk_down");
				direction = "down";
			else if (frame_movement[0] < 0)
				//setAction("walk_left");
				direction = "left";
			else if (frame_movement[0] > 0)
				//setAction("walk_right");
				direction = "right";

			setAction("walk");
		}
		else
		{
			setAction("idle");
		}

		if (canMove)
		{
			x += frame_movement[0];
			y += frame_movement[1];
		}
	}

	animation.update();

}
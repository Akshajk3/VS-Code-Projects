#include "Entity.h"

#include <cmath>
#include <vector>

std::string BASE_IMG_PATH = "Assets/Characters/images";

Entity::Entity(float p_x, float p_y, std::vector<SDL_Texture*> tex, SDL_Renderer* ren, Animation anim, std::string type)
	: x(p_x), y(p_y), textures(tex), renderer(ren), animation(anim), type(type)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 16;
	currentFrame.h = 16;
}

float Entity::getX()
{
	return x;
}

float Entity::getY()
{
	return y;
}

std::vector<SDL_Texture*> Entity::getTextures()
{
	return textures;
}

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
	if (act != action)
	{
		action = act;

		std::string filePath = BASE_IMG_PATH + "/" + action;

		textures = textureManager.loadTextures(filePath, renderer);

		animation = Animation(textures, 10, true);
	}

}

void Entity::update(int movement[2])
{
	float frame_movement[2] = { movement[0], movement[1] };

	//float* normalizedFrameMovement = normalize(frame_movement);

	if (frame_movement[0] != 0 || frame_movement[1] != 0)
	{
		if (frame_movement[1] < 0)
			setAction("walk_up");
		else if (frame_movement[1] > 0)
			setAction("walk_down");
		else if (frame_movement[0] < 0)
			setAction("walk_left");
		else if (frame_movement[0] > 0)
			setAction("walk_right");
	}
	else
	{
		setAction("idle_down");
	}

	std::cout << action << std::endl;

	animation.update();

	x += frame_movement[0];
	y += frame_movement[1];
}

float* Entity::normalize(float movement[2])
{
	float length = std::sqrt(movement[0] * movement[0] + movement[1] + movement[1]);

	float normalizedMovement[2];

	if (length != 0.0)
	{
		normalizedMovement[0] = movement[0] / length;
		normalizedMovement[1] = movement[1] / length;
	}

	return normalizedMovement;
}
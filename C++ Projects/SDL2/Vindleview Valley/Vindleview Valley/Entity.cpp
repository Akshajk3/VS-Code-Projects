#include "Entity.h"

#include <cmath>
#include <vector>

Entity::Entity(float p_x, float p_y, SDL_Texture* tex)
	: x(p_x), y(p_y), texture(tex)
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

SDL_Texture* Entity::getTexture()
{
	return texture;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

void Entity::update(int movement[2])
{
	float frame_movement[2] = { movement[0], movement[1] };

	//float* normalizedFrameMovement = normalize(frame_movement);

	x += frame_movement[0];
	y += frame_movement[1];

	std::cout << x << "," << y << std::endl;
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
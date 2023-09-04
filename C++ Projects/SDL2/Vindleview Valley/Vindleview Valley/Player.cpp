#include "Player.h"

Player::Player(float p_x, float p_y, SDL_Renderer* ren, Animation anim, std::map<std::string, std::vector<SDL_Texture*>> asset)
	: Entity(p_x, p_y, ren, anim, "player", asset)
{

}

void Player::update(int movement[2])
{
	float frame_movement[2] = { static_cast<float>(movement[0]), static_cast<float>(movement[1]) };

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

	Entity::update();
}

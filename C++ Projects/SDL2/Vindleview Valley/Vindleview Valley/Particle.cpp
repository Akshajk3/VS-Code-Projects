#include "Particle.h"

Particle::Particle(float p_x, float p_y, int scale, std::vector<SDL_Texture*> sprites, SDL_Renderer* ren)
	: x(p_x), y(p_y), textures(sprites), renderer(ren), anim(textures, 5, false)
{
	src.x = 0;
	src.y = 0;

	src.w = dest.w = 32 * scale;
	src.h = dest.h = 32 * scale;
	dest.x = x - (src.w / 2);
	dest.y = y - (src.h / 2);
}

void Particle::update()
{
	kill = false;
	if (anim.done == true)
		kill = true;

	anim.update();
}

void Particle::render(int cameraX, int cameraY)
{
	dest.x = x - cameraX;
	dest.y = y - cameraY;

	SDL_RenderCopy(renderer, anim.img(), &src, &dest);
}
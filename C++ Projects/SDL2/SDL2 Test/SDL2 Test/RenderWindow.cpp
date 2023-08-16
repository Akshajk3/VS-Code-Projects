#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* windowName, int width, int height)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

	if (window == NULL)
		std::cout << "Failed to Create SDL_Window. Error: " << SDL_GetError() << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* filepath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filepath);

	if (texture == nullptr)
	{
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	}

	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& entity)
{
	SDL_Rect src;
	src.x = entity.getCurrentFrame().x;
	src.y = entity.getCurrentFrame().y;
	src.w = entity.getCurrentFrame().w;
	src.h = entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = entity.getX() * 4;
	dst.y = entity.getY() * 4;
	dst.w =	entity.getCurrentFrame().w * 4;
	dst.h = entity.getCurrentFrame().h * 4;

	SDL_RenderCopy(renderer, entity.getTexture(), &src, &dst);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}
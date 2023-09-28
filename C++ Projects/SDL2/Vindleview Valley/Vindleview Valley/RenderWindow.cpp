#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* windowName, int width, int height)
{
	window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "Failed to Create Window. SDL_Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << "Failed to Create Renderer. SDL_Error: " << SDL_GetError() << std::endl;
	}
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, filePath);

	if (texture == NULL)
	{
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;
	}

	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& entity, int entityScale, int offset[2])
{	
	//int screenWidth = 800;
	//int screenHeight = 600;

	SDL_Rect src;
	src.x = entity.getCurrentFrame().x;
	src.y = entity.getCurrentFrame().y;
	src.w = entity.getCurrentFrame().w;
	src.h = entity.getCurrentFrame().h;

	int entityWidth = entity.getCurrentFrame().w * entityScale;
	int entityHeight = entity.getCurrentFrame().h * entityScale;

	SDL_Rect dest;
	dest.x = entity.getX() * entityScale - entityWidth / 2 + offset[0];
	dest.y = entity.getY() * entityScale - entityHeight / 2 + offset[1];
	dest.w = entity.getCurrentFrame().w * entityScale;
	dest.h = entity.getCurrentFrame().h * entityScale;

	SDL_RenderCopy(renderer, entity.getAnimation().img(), &src, &dest);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

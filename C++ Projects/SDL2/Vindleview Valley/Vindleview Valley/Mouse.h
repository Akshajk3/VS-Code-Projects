#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Mouse
{
public:
	Mouse()
	{
		SDL_Surface* mouseSurface = IMG_Load("Assets/Mouse_sprites/Cursor_1.png");
		SDL_Cursor* mouseCursor = SDL_CreateColorCursor(mouseSurface, 0, 0);
		SDL_SetCursor(mouseCursor);
	}
private:
	SDL_Texture* texture;
};
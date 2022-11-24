#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstdlib>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SQUARE_SIZE 50

int main(int argc, char** argv)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL Failed to Init. Error: " << SDL_GetError() << std::endl;
	}

	SDL_Window *window = SDL_CreateWindow("Win Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if(!window)
	{
		std::cout << "Window failed to intialize. Error: " << SDL_GetError() << std::endl;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(!renderer)
	{
		std::cout << "Renderer failed to init. Error: " << SDL_GetError() << std::endl;
	}

	SDL_Surface *win_surface = SDL_GetWindowSurface(window);
	if(!win_surface)
	{
		std::cout << "how u have 3060ti and not even get win sur in this garbaj code. Error: " << SDL_GetError() << std::endl;
	}

	SDL_Rect rect = {0, 0, 1000, 1000};
	rect.x = SCREEN_WIDTH/2;
	rect.y = SCREEN_HEIGHT/2;
	rect.w = SQUARE_SIZE;
	rect.h = SQUARE_SIZE;
	SDL_Event event;
	bool run = true;
	int green = 255;
	int red = 255;
	int blue = 255;
	float velocity = 1;
	float v_velocity = 1;
	float h_velocity = 1;

	while(run)
	{
		while(SDL_PollEvent(&event))
		{
			if(event.type == SDL_QUIT)
			{
				run = false;
				SDL_Quit();
			}

			if(event.type == SDL_MOUSEBUTTONDOWN)
			{
				green = 0+(rand()%255);
				red = 0+(rand()%255);
				blue = 0+(rand()%255);
				//rect.w = 50+(rand()%255);
				//rect.h = 50+(rand()%400);
			}

			if(event.type == SDLK_w)
			{
				v_velocity = 1;
				std::cout << "Pressed w" << std::endl;
			}
			else if(event.type == SDLK_s)
			{
				v_velocity = -1;
			}

			if(event.type == SDLK_d)
			{
				h_velocity = 1;
			}
			else if(event.type = SDLK_a)
			{
				h_velocity = -1;
			}
		}

		rect.y += v_velocity;
		rect.x += h_velocity;

		std::cout << rect.y << " " << velocity << std::endl;

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderClear(renderer);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderFillRect(renderer, &rect);

		SDL_RenderPresent(renderer);
	}

	return 0;
}
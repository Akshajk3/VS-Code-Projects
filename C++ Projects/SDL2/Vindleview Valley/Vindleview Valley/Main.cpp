#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <vector>
#include <string>
#include <random>

#include "RenderWindow.h"
#include "TextureManager.h"
#include "Entity.h"
#include "Animation.h"
#include "Tilemap.h"
#include "Player.h"
#include "Plant.h"
#include "Item.h"
#include "Tree.h"
#include "Particle.h"
#include "Building.h"
#include "Inventory.h"

int grass[40][50] = {
    { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
};

int plants[40][50] = {
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
};

const int displayWidth = 800;
const int displayHeight = 600;

const int worldWidth = 100;
const int worldHeight = 100;

int cameraX = 0;
int cameraY = 0;

int randomRange(int min, int max)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(min, max);
    
    return distr(eng);
}

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		std::cout << "SDL Failed to Init. SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "SDL Image Failed to Init. SDL_Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	RenderWindow window("Vindleview Valley", displayWidth, displayHeight);

	TextureManager textureManager;

	std::map<std::string, std::vector<SDL_Texture*>> assets;

	std::map<std::string, std::string> assetPaths;

// Player Asset Paths
	assetPaths["idle_down"] = ("Assets/Characters/images/idle_down");
	assetPaths["walk_down"] = ("Assets/Characters/images/walk_down");
	assetPaths["hoe_down"] = ("Assets/Characters/images/hoe_down");
	assetPaths["axe_down"] = ("Assets/Characters/images/axe_down");
	assetPaths["water_down"] = ("Assets/Characters/images/water_down");
	assetPaths["idle_left"] = ("Assets/Characters/images/idle_left");
	assetPaths["walk_left"] = ("Assets/Characters/images/walk_left");
	assetPaths["hoe_left"] = ("Assets/Characters/images/hoe_left");
	assetPaths["axe_left"] = ("Assets/Characters/images/axe_left");
	assetPaths["water_left"] = ("Assets/Characters/images/water_left");
	assetPaths["idle_right"] = ("Assets/Characters/images/idle_right");
	assetPaths["walk_right"] = ("Assets/Characters/images/walk_right");
	assetPaths["hoe_right"] = ("Assets/Characters/images/hoe_right");
	assetPaths["axe_right"] = ("Assets/Characters/images/axe_right");
	assetPaths["water_right"] = ("Assets/Characters/images/water_right");
	assetPaths["idle_up"] = ("Assets/Characters/images/idle_up");
	assetPaths["walk_up"] = ("Assets/Characters/images/walk_up");
	assetPaths["hoe_up"] = ("Assets/Characters/images/hoe_up");
	assetPaths["axe_up"] = ("Assets/Characters/images/axe_up");
	assetPaths["water_up"] = ("Assets/Characters/images/water_up");

// Entity Asset Paths
	assetPaths["cow_idle"] = ("Assets/Characters/images/cow/idle");
	assetPaths["chicken_idle"] = ("Assets/Characters/images/chicken/idle");
	
// Tilemap Asset Paths
	assetPaths["grass"] = ("Assets/Tilesets/images/grass");
	assetPaths["fence"] = ("Assets/Tilesets/images/fence");
	assetPaths["till"] = ("Assets/Tilesets/images/till");

// UI Asset Paths
	assetPaths["hoe"] = ("Assets/Objects/images/Basic tools and meterials_2.png");
	assetPaths["axe"] = ("Assets/Objects/images/Basic tools and meterials_1.png");
	assetPaths["water"] = ("Assets/Objects/images/Basic tools and meterials_0.png");
    assetPaths["wheatBag"] = ("Assets/Objects/images/wheat/00.png");
    assetPaths["beetBag"] = ("Assets/Objects/images/beet/00.png");
    
// Plant Asests Paths
    assetPaths["wheat"] = ("Assets/Objects/images/wheat");
	assetPaths["beet"] = ("Assets/Objects/images/beet");

// Tree Asset Paths
	assetPaths["tree1"] = ("Assets/Objects/images/trees1");
	assetPaths["tree2"] = ("Assets/Objects/images/trees2");

// Item Asset Paths
	assetPaths["wood"] = ("Assets/Objects/images/wood");

// Mouse Asset Paths
	assetPaths["cursor"] = ("Assets/Mouse_sprites");

// Particle Asset Paths
	assetPaths["smoke"] = ("Assets/Particles/Smoke");

// Building Asset Paths
    assetPaths["house"] = ("Assets/Objects/House.png");

// Inventory Asset Paths
	assetPaths["inv"] = ("Assets/Inventory/tiles");

// Chest Asset Paths
	assetPaths["chest"] = ("Assets/Objects/images/chest");
	
// Player Assets
	assets["idle_down"] = textureManager.loadTextures(assetPaths["idle_down"], window.renderer);
	assets["walk_down"] = textureManager.loadTextures(assetPaths["walk_down"], window.renderer);
	assets["hoe_down"] = textureManager.loadTextures(assetPaths["hoe_down"], window.renderer);
	assets["axe_down"] = textureManager.loadTextures(assetPaths["axe_down"], window.renderer);
	assets["water_down"] = textureManager.loadTextures(assetPaths["water_down"], window.renderer);
	assets["idle_left"] = textureManager.loadTextures(assetPaths["idle_left"], window.renderer);
	assets["walk_left"] = textureManager.loadTextures(assetPaths["walk_left"], window.renderer);
	assets["hoe_left"] = textureManager.loadTextures(assetPaths["hoe_left"], window.renderer);
	assets["axe_left"] = textureManager.loadTextures(assetPaths["axe_left"], window.renderer);
	assets["water_left"] = textureManager.loadTextures(assetPaths["water_left"], window.renderer);
	assets["idle_right"] = textureManager.loadTextures(assetPaths["idle_right"], window.renderer);
	assets["walk_right"] = textureManager.loadTextures(assetPaths["walk_right"], window.renderer);
	assets["hoe_right"] = textureManager.loadTextures(assetPaths["hoe_right"], window.renderer);
	assets["axe_right"] = textureManager.loadTextures(assetPaths["axe_right"], window.renderer);
	assets["water_right"] = textureManager.loadTextures(assetPaths["water_right"], window.renderer);
	assets["idle_up"] = textureManager.loadTextures(assetPaths["idle_up"], window.renderer);
	assets["walk_up"] = textureManager.loadTextures(assetPaths["walk_up"], window.renderer);
	assets["hoe_up"] = textureManager.loadTextures(assetPaths["hoe_up"], window.renderer);
	assets["axe_up"] = textureManager.loadTextures(assetPaths["axe_up"], window.renderer);
	assets["water_up"] = textureManager.loadTextures(assetPaths["water_up"], window.renderer);

// Entity Assets
	assets["cow_idle"] = textureManager.loadTextures(assetPaths["cow_idle"], window.renderer);
	assets["chicken_idle"] = textureManager.loadTextures(assetPaths["chicken_idle"], window.renderer);

// Tilemap Assets
	assets["grass"] = textureManager.loadTextures(assetPaths["grass"], window.renderer);
	assets["fence"] = textureManager.loadTextures(assetPaths["fence"], window.renderer);
	assets["till"] = textureManager.loadTextures(assetPaths["till"], window.renderer);

// Inventory Assets
	assets["inv"] = textureManager.loadTextures(assetPaths["inv"], window.renderer);
    
// Building Assets
    SDL_Texture* houseTex = textureManager.loadTexture(assetPaths["house"].c_str(), window.renderer);

// UI Assets
	SDL_Texture* cursorTexture = textureManager.loadTexture("Assets/Mouse_sprites/03.png", window.renderer);
	SDL_Texture* hoe_icon = textureManager.loadTexture(assetPaths["hoe"].c_str(), window.renderer);
	SDL_Texture* axe_icon = textureManager.loadTexture(assetPaths["axe"].c_str(), window.renderer);
	SDL_Texture* water_icon = textureManager.loadTexture(assetPaths["water"].c_str(), window.renderer);
    SDL_Texture* wheat_icon = textureManager.loadTexture(assetPaths["wheatBag"].c_str(), window.renderer);
	SDL_Texture* beet_icon = textureManager.loadTexture(assetPaths["beetBag"].c_str(), window.renderer);

// Plant Assets
    assets["wheat"] = textureManager.loadTextures(assetPaths["wheat"], window.renderer);
	assets["beet"] = textureManager.loadTextures(assetPaths["beet"], window.renderer);

// Tree Assets
	assets["tree1"] = textureManager.loadTextures(assetPaths["tree1"], window.renderer);
	assets["tree2"] = textureManager.loadTextures(assetPaths["tree2"], window.renderer);

// Item Assets
	assets["wood"] = textureManager.loadTextures(assetPaths["wood"], window.renderer);

// Mouse Assets
	assets["cursor"] = textureManager.loadTextures(assetPaths["cursor"], window.renderer);

// Particle Assets
	assets["smoke"] = textureManager.loadTextures(assetPaths["smoke"], window.renderer);

// Chest Assets
	assets["chest"] = textureManager.loadTextures(assetPaths["chest"], window.renderer);

	SDL_ShowCursor(SDL_DISABLE);

	Player player(400, 300, window.renderer, assets);
	
	Entity cow(100, 10, window.renderer, "cow", assets);
	Entity chicken(100, 100, window.renderer, "chicken", assets);

	Tilemap backGroundTilemap(assets, 40, 50);
    backGroundTilemap.LoadMap(grass);
    
    Tilemap plantTiles(assets, 40, 50);
    plantTiles.LoadMap(plants);

	Inventory inventory(assets["inv"]);
	Inventory buildMenue(assets["inv"]);
	Item houseItem = Item(0, 0, "inventoryIcon", 0, houseTex, 2);
	Item chestItem = Item(0, 0, "inventoryIcon", 0, assets["chest"][0], 2);
	buildMenue.addItem(houseItem);
	buildMenue.addItem(chestItem);

	//Tilemap treeTiles(assets);
	//treeTiles.LoadMap(trees);

    std::vector<Tree> Trees;
    
	for (int x = 0; x < 50; x++)
	{
		auto it = Trees.begin() + x;

        Trees.push_back(Tree(randomRange(50, 1500), randomRange(100, 1100), 0, assets["tree1"], window.renderer));
		if (Trees[x].checkClick(cow.getCurrentFrame()) || Trees[x].checkClick(chicken.getCurrentFrame()) || Trees[x].checkClick(player.getCurrentFrame()))
		{
			Trees.erase(it);
		}
	}

    Building house1(100, 100, houseTex, window.renderer, false, false);

	std::vector<Building> buildings;
    
    std::vector<Plant> Plants;
    std::vector<Item> Items;
	std::vector<Particle> Particles;

	bool movement[4] = {false, false, false, false};

	int mouseX;
	int	mouseY;
    
    int wood = 0;

	bool selecting = false;

	bool isRunning = true;

	bool show = false;

	SDL_Event event;
    
    int scroll[2] = {0, 0};

	while (isRunning)
	{
		frameStart = SDL_GetTicks();

		bool toolClick = false;
		bool itemClick = false;
		bool rightClick = false;

		SDL_GetMouseState(&mouseX, &mouseY);

		SDL_Rect cursorRect = { mouseX, mouseY, 32, 32 };


		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}

			if (event.type == SDL_KEYDOWN)
			{
				SDL_Keycode keyCode = event.key.keysym.sym;
				if (keyCode == SDLK_d)
				{
					movement[0] = true;
				}
				if (keyCode == SDLK_a)
				{
					movement[1] = true;
				}
				if (keyCode == SDLK_s)
				{
					movement[2] = true;
				}
				if (keyCode == SDLK_w)
				{
					movement[3] = true;
				}
				if (keyCode == SDLK_1)
				{
					player.setTool("hoe");
				}
				if (keyCode == SDLK_2)
				{
					player.setTool("axe");
				}
				if (keyCode == SDLK_3)
				{
					player.setTool("water");
				}
				if (keyCode == SDLK_4)
				{
					player.setTool("wheat");
				}
				if (keyCode == SDLK_5)
				{
					player.setTool("beet");
				}
				if (keyCode == SDLK_6)
				{
					player.setTool("build");
				}
				if (keyCode == SDLK_e)
				{
					show = !show;
					inventory.show = !inventory.show;
					buildMenue.show = false;
				}
				if (keyCode == SDLK_f)
				{
					show = !show;
					buildMenue.show = !buildMenue.show;
					inventory.show = false;
				}
				
			}
			if (event.type == SDL_KEYUP)
			{
				SDL_Keycode keyCode = event.key.keysym.sym;
				if (keyCode == SDLK_d)
				{
					movement[0] = false;
				}
				if (keyCode == SDLK_a)
				{
					movement[1] = false;
				}
				if (keyCode == SDLK_s)
				{
					movement[2] = false;
				}
				if (keyCode == SDLK_w)
				{
					movement[3] = false;
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (player.getTimer() == 0 && selecting == false && show == false)
					{
						player.act();

						if (player.getTool() == "hoe")
							backGroundTilemap.setTile(mouseX, mouseY, 2);
						if (player.getTool() == "wheat" && backGroundTilemap.getTile(mouseX, mouseY) == 2 && plantTiles.getTile(mouseX, mouseY) == 0)
						{
							plantTiles.setTile(mouseX, mouseY, 3);
							Plants.push_back(Plant(mouseX, mouseY, "wheat", 10000, &plantTiles));
						}
						if (player.getTool() == "beet" && backGroundTilemap.getTile(mouseX, mouseY) == 2 && plantTiles.getTile(mouseX, mouseY) == 0)
						{
							plantTiles.setTile(mouseX, mouseY, 7);
							Plants.push_back(Plant(mouseX, mouseY, "beet", 10000, &plantTiles));
						}
						toolClick = true;
					}
					else
						itemClick = true;

					if (player.getTool() == "build" && wood >= 5 && show == false)
					{
						inventory.removeItem(0, 5);
						wood -= 5;
						buildings.push_back(Building(mouseX, mouseY, houseTex, window.renderer, true));
					}
				}
				if (event.button.button == SDL_BUTTON_RIGHT)
				{
					rightClick = true;
				}
			}
		}

		int move[2] = { movement[0] - movement[1], movement[2] - movement[3] };

		//int displayWidth = 800;
		//int displayHeight = 600;

		if(player.canMove)
		{
			int cameraSpeed = 4;

			if (move[0] == 1)
			{
				scroll[0] -= -cameraSpeed;
			}
			if (move[0] == -1)
			{
				scroll[0] -= cameraSpeed;
			}
			if (move[1] == 1)
			{
				scroll[1] -= -cameraSpeed;
			}
			if (move[1] == -1)
			{
				scroll[1] -= cameraSpeed;
			}
		}

		//std::cout << "MouseX: " << mouseX << std::endl;
		//std::cout << "MouseY: " << mouseY << std::endl;

		//cameraX = std::clamp(cameraX, 0, worldWidth - displayWidth);
		//cameraY = std::clamp(cameraY, 0, worldHeight - displayHeight);

		//std::cout << "Player X: " << player.getX() << std::endl;
		//std::cout << "Player Y: " << player.getY() << std::endl;

		int render_scroll[2] = { cameraX, cameraY };

		window.clear();
		player.update(move);
		cow.update();
		chicken.update();
		backGroundTilemap.DrawMap(window.renderer, scroll[0], scroll[1]);
		plantTiles.DrawMap(window.renderer, scroll[0], scroll[1]);
		window.render(cow, 4, scroll[0], scroll[1], false);
		window.render(chicken, 2, scroll[0], scroll[1], false);
		window.render(player, 4, scroll[0], scroll[1], true, displayWidth, displayHeight);

		if (player.getTool() == "build" && house1.isPlaced() == false)
		{
			house1.update(mouseX, mouseY);
			house1.render(0, 0);
		}
		else if (house1.isPlaced() == true)
		{
			house1.render(scroll[0], scroll[1]);
		}

		for (Building& house : buildings)
		{
			house.render(scroll[0], scroll[1]);
		}
        
		auto its = Plants.begin();
		while (its != Plants.end())
        {
            Plant& plant = *its;
            
            plant.update();

			//std::cout << Plants.size() << std::endl;
            
			if (rightClick == true && player.getTool() == "hoe" && plantTiles.getTile(mouseX, mouseY) == 6)
			{
				plantTiles.setTile(mouseX, mouseY, 0);
				Items.push_back(Item(mouseX, mouseY, "Wheat", 0, assets["wheat"][5]));
				Particles.push_back(Particle(plant.getX(), plant.getY() - 50, 4, assets["smoke"], window.renderer));
				its = Plants.erase(its);
			}
			else if (rightClick == true && player.getTool() == "hoe" && plantTiles.getTile(mouseX, mouseY) == 10)
			{
				plantTiles.setTile(mouseX, mouseY, 0);
				Items.push_back(Item(mouseX, mouseY, "Beet", 0, assets["beet"][5]));
				Particles.push_back(Particle(plant.getX(), plant.getY() - 50, 4, assets["smoke"], window.renderer));
				its = Plants.erase(its);
			}
			else
			{
				++its;
			}
        }
        
        bool collisionDectected = false;
        selecting = false;
        
        for (Tree& tree : Trees)
        {
            tree.render(scroll[0], scroll[1]);
            
            if (tree.checkClick(cursorRect) && tree.dead == false && show == false)
            {
                collisionDectected = true;
            }
            
            if (player.getTool() == "axe" && tree.checkClick(cursorRect) && tree.dead == false && toolClick == true)
            {
                tree.die();
                Particles.push_back(Particle(tree.getX(), tree.getY() - 100, 10, assets["smoke"], window.renderer));
                Items.push_back(Item(tree.getX(), tree.getY() - 50, "wood", 0, assets["wood"][0], 1.5));
            }
        }

		auto it = Items.begin();
		while (it != Items.end())
		{
			Item& item = *it;

			item.update();
			item.render(window.renderer, scroll);
			if (item.checkMouse(cursorRect))
			{
				collisionDectected = true;
				selecting = true;
			}

			if (item.checkMouse(cursorRect) && itemClick == true)
			{
				if (item.getType() == "wood")
					wood += 1;

				inventory.addItem(item);

				it = Items.erase(it);
			}
			else
			{
				++it;
			}
		}

        for (auto it = Particles.begin(); it != Particles.end();)
        {
            Particle& particle = *it;

            particle.update();
            particle.render(scroll[0], scroll[1]);
            if (particle.kill)
            {
                it = Particles.erase(it);
            }
            else
            {
                ++it;
            }
        }
        
        if (collisionDectected)
        {
            cursorTexture = assets["cursor"][2];
        }
        else
        {
            cursorTexture = assets["cursor"][3];
        }

		inventory.render(window.renderer);
		buildMenue.render(window.renderer);

		SDL_Rect toolRect = { 0, 0, 64, 64 };

		if (player.getTool() == "hoe")
		{
			SDL_RenderCopy(window.renderer, hoe_icon, nullptr, &toolRect);	
		}
		if (player.getTool() == "axe")
		{
			SDL_RenderCopy(window.renderer, axe_icon, nullptr, &toolRect);
		}
		if (player.getTool() == "water")
		{
			SDL_RenderCopy(window.renderer, water_icon, nullptr, &toolRect);
		}
        if (player.getTool() == "wheat")
        {
            SDL_RenderCopy(window.renderer, wheat_icon, nullptr, &toolRect);
        }
		if (player.getTool() == "beet")
		{
			SDL_RenderCopy(window.renderer, beet_icon, nullptr, &toolRect);
		}
		if (player.getTool() == "build")
		{
			SDL_RenderCopy(window.renderer, assets["cursor"][1], nullptr, &toolRect);
		}

		SDL_RenderCopy(window.renderer, cursorTexture, nullptr, &cursorRect);

		//std::cout << tilemap.getTile(mouseX, mouseY);

		window.display();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	window.cleanUp();
	IMG_Quit();
	SDL_Quit();
	return 0;
}

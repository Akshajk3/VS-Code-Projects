#pragma once

#include <vector>

#include "Chunk.h"

#define WORLD_WIDTH 4
#define WORLD_HEIGHT 4

class World
{
public:
	World();
	~World();

	void DrawChunks();
	void DeleteChunks();

private:
	std::vector<Chunk> chunks;
};

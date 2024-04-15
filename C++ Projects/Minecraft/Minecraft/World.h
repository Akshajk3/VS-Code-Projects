#pragma once

#include <vector>

#include "Chunk.h"

class World
{
public:
	World(int width, int height);
	~World();

	void DrawChunks();
	void DeleteChunks();

private:
	std::vector<std::vector<Chunk>> chunks;
};

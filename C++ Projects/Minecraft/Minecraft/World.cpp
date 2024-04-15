#include "World.h"

World::World(int width, int height)
{
    chunks.resize(width);
    
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            chunks[x].push_back(glm::vec2(x, y));
        }
    }
}


World::~World()
{
    
}


void World::DrawChunks()
{
    for (auto& column : chunks)
    {
        for (auto& chunk : column)
        {
            chunk.DrawChunk();
        }
    }
}

void World::DeleteChunks()
{
    
}

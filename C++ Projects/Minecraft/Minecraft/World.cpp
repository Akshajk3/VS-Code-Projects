#include "World.h"

World::World()
{
    for (int x = 0; x < WORLD_WIDTH; x++)
    {
        for (int y = 0; y < WORLD_WIDTH; y++)
        {
            chunks.push_back(Chunk(glm::vec2(x, y)));
        }
    }
}

World::~World()
{
    
}

void World::DrawChunks()
{
    for (auto& chunk : chunks)
    {
        chunk.DrawChunk();
    }
}

void World::DeleteChunks()
{
    for (auto& chunk : chunks)
    {
        chunk.DeleteChunk();
    }
}

#include "Chunk.h"

Chunk::Chunk(glm::vec2 pos)
{
	// Resize the blocks vector to the chunk dimensions
	blocks.resize(CHUNK_WIDTH, std::vector<std::vector<int>>(CHUNK_HEIGHT, std::vector<int>(CHUNK_LENGTH)));

	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < CHUNK_LENGTH; z++)
			{
				int worldX = pos.x * CHUNK_WIDTH + x;
				int worldY = y;
				int worldZ = pos.y * CHUNK_LENGTH + z;

				blocks[x][y][z] = 1;

				if (blocks[x][y][z] == 1)
				{
					blockMeshes.push_back(BlockType(glm::vec3(worldX, worldY, worldZ)));
				}
			}
		}
	}
	std::cout << blockMeshes.size() << std::endl;
}

Chunk::~Chunk()
{
	blocks.clear();
}

void Chunk::DrawChunk()
{
	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < CHUNK_LENGTH; z++)
			{
				if (blocks[x][y][z] == 1)
				{
					bool drawLeft = (x == 0 || blocks[x - 1][y][z] != 1);
					bool drawRight = (x == CHUNK_WIDTH - 1 || blocks[x + 1][y][z] != 1);
					bool drawBottom = (y == 0 || blocks[x][y - 1][z] != 1);
					bool drawTop = (y == CHUNK_HEIGHT - 1 || blocks[x][y + 1][z] != 1);
					bool drawBack = (z == 0 || blocks[x][y][z - 1] != 1);
					bool drawFront = (z == CHUNK_LENGTH - 1 || blocks[x][y][z + 1] != 1);

					if (y > 14)
					{
						grassTex.Bind();
					}
					else if (y > 10)
					{
						dirtTex.Bind();
					}
					else
					{
						stoneTex.Bind();
					}

					if (drawLeft || drawRight || drawBottom || drawTop || drawBack || drawFront)
					{
						blockMeshes[(x * CHUNK_HEIGHT * CHUNK_LENGTH) + (y * CHUNK_LENGTH) + z].Draw();
					}
				}
			}
		}
	}
}

void Chunk::DeleteChunk()
{
	for (auto& block : blockMeshes)
	{
		block.Delete();
	}
	blockMeshes.clear();
}
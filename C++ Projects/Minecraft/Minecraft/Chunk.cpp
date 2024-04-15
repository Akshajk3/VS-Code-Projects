#include "Chunk.h"

Chunk::Chunk(glm::vec2 pos)
    : position(pos)
{
	// Resize the blocks vector to the chunk dimensions
	blocks.resize(CHUNK_WIDTH, std::vector<std::vector<int>>(CHUNK_HEIGHT, std::vector<int>(CHUNK_LENGTH)));
    

	for (int x = 0; x < CHUNK_WIDTH; x++)
	{
		for (int y = 0; y < CHUNK_HEIGHT; y++)
		{
			for (int z = 0; z < CHUNK_LENGTH; z++)
			{
                if (y > 14)
                {
                    blocks[x][y][z] = 1;
                }
                else if (y > 10)
                {
                    blocks[x][y][z] = 2;
                }
                else
                {
                    blocks[x][y][z] = 3;
                }
			}
		}
	}
    
    GenerateMesh();
    
	std::cout << meshVertexPositions.size() << std::endl;
}

Chunk::~Chunk()
{
	blocks.clear();
}

void Chunk::GenerateMesh()
{
    meshVertexPositions.clear();
    meshTexCoords.clear();
    meshShadingValues.clear();
    meshIndices.clear();
    
    for (int x = 0; x < CHUNK_WIDTH; x++)
    {
        for (int y = 0; y < CHUNK_HEIGHT; y++)
        {
            for (int z = 0; z < CHUNK_LENGTH; z++)
            {
                int worldX = position.x * CHUNK_WIDTH + x;
                int worldY = y;
                int worldZ = position.y * CHUNK_LENGTH + z;
                
                if (IsBlockHidden(x, y, z, 0) == -1)
                {
                    BlockType* block = new BlockType(glm::vec3(worldX, worldY, worldZ));
                    
                    std::vector<GLfloat> blockVertexPosition = block->getVertexPositions();
                    std::vector<GLfloat> blockTexCoords = block->getTexCoords();
                    std::vector<GLfloat> blockShadingValues = block->getShadingValues();
                    
                    meshVertexPositions.insert(meshVertexPositions.end(), blockVertexPosition.begin(), blockVertexPosition.end());
                    meshTexCoords.insert(meshTexCoords.end(), blockTexCoords.begin(), blockTexCoords.end());
                    meshShadingValues.insert(meshShadingValues.end(), blockShadingValues.begin(), blockShadingValues.end());
                    
                    Numbers numbers;
                    
                    GLuint baseIndex = meshVertexPositions.size() / 3;
                    for (GLuint index : numbers.indices)
                        meshIndices.push_back(baseIndex + index);
                    
                    delete block;
                }
            }
        }
    }
    
    vao.Bind();
    
    VBO vertVBO(meshVertexPositions);
    VBO texVBO(meshTexCoords);
    VBO shadingVBO(meshShadingValues);
    
    EBO ebo(meshIndices);
    
    vao.LinkAttrib(vertVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    vao.LinkAttrib(texVBO, 1, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
    vao.LinkAttrib(shadingVBO, 2, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);
    
    vao.Unbind();
    vertVBO.Unbind();
    texVBO.Unbind();
    shadingVBO.Unbind();
    ebo.Unbind();
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
                    //grassTex.Bind();
                }
                if (blocks[x][y][z] == 2)
                {
                    dirtTex.Bind();
                }
                if (blocks[x][y][z] == 3)
                {
                    stoneTex.Bind();
                }
            }
        }
    }
    vao.Bind();
    glDrawElements(GL_TRIANGLES, meshIndices.size(), GL_UNSIGNED_INT, 0);
}

int Chunk::IsBlockHidden(int x, int y, int z, int face) const
{
    // Check if the block is surrounded by other blocks on all six sides
    if (x > 0 && x < CHUNK_WIDTH - 1 &&
        y > 0 && y < CHUNK_HEIGHT - 1 &&
        z > 0 && z < CHUNK_LENGTH - 1) {
        // Check if neighboring blocks are solid
        // Left face hidden
        if (blocks[x - 1][y][z])
            return 0;
        // Right face hidden
        if (blocks[x + 1][y][z])
            return 1;
        // Bottom face hidden
        if (blocks[x][y - 1][z])
            return 2;
        // Top face hidden
        if (blocks[x][y + 1][z])
            return 3;
        // Back face hidden
        if (blocks[x][y][z - 1])
            return 4;
        // Front face hidden
        if (blocks[x][y][z + 1])
            return 5;
    }
    return -1; // Block is not hidden
}

void Chunk::DeleteChunk()
{
    vao.Delete();
    meshVertexPositions.clear();
    meshTexCoords.clear();
    meshShadingValues.clear();
    meshIndices.clear();
}

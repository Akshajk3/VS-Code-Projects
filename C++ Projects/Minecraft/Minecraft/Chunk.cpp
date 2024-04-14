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
				blocks[x][y][z] = 1;
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
                if (blocks[x][y][z] && !IsBlockHidden(x, y, z))
                {
                    int worldX = position.x * CHUNK_WIDTH + x;
                    int worldY = y;
                    int worldZ = position.y * CHUNK_LENGTH + z;
                    
                    BlockType block(glm::vec3(worldX, worldY, worldZ));
                    
                    std::vector<GLfloat> blockVertexPosition = block.getVertexPositions();
                    std::vector<GLfloat> blockTexCoords = block.getTexCoords();
                    std::vector<GLfloat> blockShadingValues = block.getShadingValues();
                    
                    meshVertexPositions.insert(meshVertexPositions.end(), blockVertexPosition.begin(), blockVertexPosition.end());
                    meshTexCoords.insert(meshTexCoords.end(), blockTexCoords.begin(), blockTexCoords.end());
                    meshShadingValues.insert(meshShadingValues.end(), blockShadingValues.begin(), blockShadingValues.end());
                    
                    Numbers numbers;
                    
                    GLuint baseIndex = meshVertexPositions.size() / 3;
                    for (GLuint index : numbers.indices)
                        meshIndices.push_back(baseIndex + index);
                    
                    block.Delete();
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
    grassTex.Bind();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, meshIndices.size(), GL_UNSIGNED_INT, 0);
}

bool Chunk::IsBlockHidden(int x, int y, int z) const
{
    return false;
}

void Chunk::DeleteChunk()
{
    vao.Delete();
    meshVertexPositions.clear();
    meshTexCoords.clear();
    meshShadingValues.clear();
    meshIndices.clear();
}

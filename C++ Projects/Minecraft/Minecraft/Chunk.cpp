#include "Chunk.h"

Chunk::Chunk(glm::vec2 pos)
    : position(pos)
{
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
}

Chunk::~Chunk()
{
    vao.Delete();
    meshVertexPositions.clear();
    meshTexCoords.clear();
    meshShadingValues.clear();
    meshIndices.clear();
}

void Chunk::GenerateMesh()
{
    Numbers numbers;
    
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
                if (blocks[x][y][z] == 1)
                {
                    // Generate mesh data for each block
                    float startX = position.x * CHUNK_WIDTH;
                    float startY = 0.0; // Adjust as needed
                    float startZ = position.y * CHUNK_LENGTH;

                    // Vertex positions
                    meshVertexPositions.insert(meshVertexPositions.end(), {
                        startX + x, startY + y, startZ + z,
                        startX + x + 1, startY + y, startZ + z,
                        startX + x + 1, startY + y + 1, startZ + z,
                        startX + x, startY + y + 1, startZ + z,

                        startX + x, startY + y, startZ + z + 1,
                        startX + x + 1, startY + y, startZ + z + 1,
                        startX + x + 1, startY + y + 1, startZ + z + 1,
                        startX + x, startY + y + 1, startZ + z + 1,

                        startX + x, startY + y, startZ + z,
                        startX + x + 1, startY + y, startZ + z,
                        startX + x + 1, startY + y, startZ + z + 1,
                        startX + x, startY + y, startZ + z + 1,

                        startX + x, startY + y + 1, startZ + z,
                        startX + x + 1, startY + y + 1, startZ + z,
                        startX + x + 1, startY + y + 1, startZ + z + 1,
                        startX + x, startY + y + 1, startZ + z + 1,

                        startX + x, startY + y, startZ + z,
                        startX + x, startY + y + 1, startZ + z,
                        startX + x, startY + y + 1, startZ + z + 1,
                        startX + x, startY + y, startZ + z + 1,

                        startX + x + 1, startY + y, startZ + z,
                        startX + x + 1, startY + y + 1, startZ + z,
                        startX + x + 1, startY + y + 1, startZ + z + 1,
                        startX + x + 1, startY + y, startZ + z + 1
                        });

                    // Texture coordinates and shading values (you can adjust these as needed)
                    meshTexCoords.insert(meshTexCoords.end(), {
                        0.0f, 0.0f,
                        1.0f, 0.0f,
                        1.0f, 1.0f,
                        0.0f, 1.0f,

                        0.0f, 0.0f,
                        1.0f, 0.0f,
                        1.0f, 1.0f,
                        0.0f, 1.0f,

                        0.0f, 0.0f,
                        1.0f, 0.0f,
                        1.0f, 1.0f,
                        0.0f, 1.0f,

                        0.0f, 0.0f,
                        1.0f, 0.0f,
                        1.0f, 1.0f,
                        0.0f, 1.0f,

                        0.0f, 0.0f,
                        1.0f, 0.0f,
                        1.0f, 1.0f,
                        0.0f, 1.0f,

                        0.0f, 0.0f,
                        1.0f, 0.0f,
                        1.0f, 1.0f,
                        0.0f, 1.0f
                        });
                    meshShadingValues.insert(meshShadingValues.end(), {
                        0.6f, 0.6f, 0.6f, 0.6f,
                        0.6f, 0.6f, 0.6f, 0.6f,
                        0.6f, 0.6f, 0.6f, 0.6f,
                        0.6f, 0.6f, 0.6f, 0.6f,

                        0.6f, 0.6f, 0.6f, 0.6f,
                        0.6f, 0.6f, 0.6f, 0.6f,
                        0.6f, 0.6f, 0.6f, 0.6f,
                        0.6f, 0.6f, 0.6f, 0.6f,

                        0.4f, 0.4f, 0.4f, 0.4f,
                        0.4f, 0.4f, 0.4f, 0.4f,
                        0.4f, 0.4f, 0.4f, 0.4f,
                        0.4f, 0.4f, 0.4f, 0.4f,

                        1.0f, 1.0f, 1.0f, 1.0f,
                        1.0f, 1.0f, 1.0f, 1.0f,
                        1.0f, 1.0f, 1.0f, 1.0f,
                        1.0f, 1.0f, 1.0f, 1.0f,

                        0.8f, 0.8f, 0.8f, 0.8f,
                        0.8f, 0.8f, 0.8f, 0.8f,
                        0.8f, 0.8f, 0.8f, 0.8f,
                        0.8f, 0.8f, 0.8f, 0.8f,

                        0.8f, 0.8f, 0.8f, 0.8f,
                        0.8f, 0.8f, 0.8f, 0.8f,
                        0.8f, 0.8f, 0.8f, 0.8f,
                        0.8f, 0.8f, 0.8f, 0.8f
                        });

                    // Indices
                    GLuint baseIndex = meshVertexPositions.size() / 3 - 24; // Adjust baseIndex for the current block
                    meshIndices.insert(meshIndices.end(), {
                        baseIndex, baseIndex + 1, baseIndex + 2, baseIndex + 2, baseIndex + 3, baseIndex,
                        baseIndex + 4, baseIndex + 5, baseIndex + 6, baseIndex + 6, baseIndex + 7, baseIndex + 4,
                        baseIndex + 8, baseIndex + 9, baseIndex + 10, baseIndex + 10, baseIndex + 11, baseIndex + 8,
                        baseIndex + 12, baseIndex + 13, baseIndex + 14, baseIndex + 14, baseIndex + 15, baseIndex + 12,
                        baseIndex + 16, baseIndex + 17, baseIndex + 18, baseIndex + 18, baseIndex + 19, baseIndex + 16,
                        baseIndex + 20, baseIndex + 21, baseIndex + 22, baseIndex + 22, baseIndex + 23, baseIndex + 20
                        });
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
    vao.LinkAttrib(shadingVBO, 2, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    
    vao.Unbind();
    vertVBO.Unbind();
    texVBO.Unbind();
    shadingVBO.Unbind();
    ebo.Unbind();
}

bool Chunk::IsFaceHidden(int x, int y, int z, int face)
{
    int nx = x;
    int ny = y;
    int nz = z;
    
    switch(face)
    {
        // Front Face
        case 0:
            nz--;
            break;
        // Back Face
        case 1:
            nz++;
            break;
        // Top Face
        case 2:
            ny++;
            break;
        // Bottom Face
        case 3:
            ny--;
            break;
        // Right Face
        case 4:
            nx++;
            break;
        // Left Face
        case 5:
            nx--;
            break;
    }
    
    if (nx >= 0 && nx < CHUNK_WIDTH &&
        ny >= 0 && ny < CHUNK_HEIGHT &&
        nz >= 0 && nz < CHUNK_LENGTH)
    {
        if (blocks[x][y][z] == 1)
        {
            return true;
        }
    }
    
    return false;
}

void Chunk::DrawChunk()
{
    vao.Bind();
    glDrawElements(GL_TRIANGLES, meshIndices.size(), GL_UNSIGNED_INT, 0);
}

void Chunk::DeleteChunk()
{
    vao.Delete();
    meshVertexPositions.clear();
    meshTexCoords.clear();
    meshShadingValues.clear();
    meshIndices.clear();
}

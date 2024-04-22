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
    
    position.x *= CHUNK_WIDTH;
    position.y *= CHUNK_LENGTH;

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
                    
                    float worldX = x;
                    float worldY = y;
                    float worldZ = z;
                    
                    for (int face = 0; face < 1; face++)
                    {
                        std::vector<GLfloat> faceVertices;
                        
                        std::cout << numbers.vertices[face].size() << std::endl;
                        for (int i = 0; i < numbers.vertices[face].size(); i+=3)
                        {
                            faceVertices.push_back(numbers.vertices[face][i] + worldX);
                            faceVertices.push_back(numbers.vertices[face][i + 1] + worldY);
                            faceVertices.push_back(numbers.vertices[face][i + 2] + worldZ);
                        }
                        meshVertexPositions.insert(meshVertexPositions.end(), faceVertices.begin(), faceVertices.end());
                        
                        std::vector<GLfloat> faceTexCoords = numbers.texCoords[face];
                        meshTexCoords.insert(meshTexCoords.end(), faceTexCoords.begin(), faceTexCoords.end());
                        
                        std::vector<GLfloat> faceShadingValues = numbers.shadingValues[face];
                        meshShadingValues.insert(meshShadingValues.end(), faceShadingValues.begin(), faceShadingValues.end());
                        
                        std::vector<GLuint> faceIndices = numbers.indices[face];
                        meshIndices.insert(meshIndices.end(), faceIndices.begin(), faceIndices.end());
                    }
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

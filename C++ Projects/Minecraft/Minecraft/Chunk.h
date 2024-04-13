#pragma once

#include <glad/glad.h>
#include <vector>

#include "World.h"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16
#define CHUNK_LENGTH 16

class Chunk
{
public:
    Chunk(int position, World world);
    ~Chunk();
    
private:
    std::vector<std::vector<int>> blocks;
    std::vector<GLfloat> meshVertexPosition;
    std::vector<GLfloat> meshTexCoords;
    std::vector<GLfloat> meshShadingValues;
    std::vector<GLuint> meshIndices;
    
    GLuint VAO;
    GLuint vertexPositionVBO;
    GLuint texCoordVBO;
    GLuint shadingValueVBO;
    GLuint EBO;
    
    bool has_mesh;
    int meshIndexCounter;
};

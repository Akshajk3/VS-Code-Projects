#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>

#include "Numbers.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


#define CHUNK_WIDTH 8
#define CHUNK_HEIGHT 16
#define CHUNK_LENGTH 8
#define CHUNK_VOL CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH
#define CHUNK_AREA CHUNK_WIDTH * CHUNK_LENGTH

class Chunk
{
public:
    Chunk(glm::vec2 pos);
    ~Chunk();

    void DeleteChunk();
    void DrawChunk();
    
    void GenerateMesh();
    
    bool IsFaceHidden(int x, int y, int z, int face);
    
    glm::vec2 position;
    
private:
    int blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_LENGTH];

    std::vector<GLfloat> meshVertexPositions;
    std::vector<GLfloat> meshTexCoords;
    std::vector<GLfloat> meshShadingValues;
    std::vector<GLuint> meshIndices;
    
    Texture grassTex = Texture("textures/grass.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    VAO vao;
};

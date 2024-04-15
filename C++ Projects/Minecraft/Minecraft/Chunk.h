#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm/glm.hpp>

#include "Block.h"
#include "Numbers.h"

#define CHUNK_WIDTH 8
#define CHUNK_HEIGHT 16
#define CHUNK_LENGTH 8

class Chunk
{
public:
    Chunk(glm::vec2 pos);
    ~Chunk();

    void DeleteChunk();
    void DrawChunk();

    int GetX();
    int GetY();
    
    int IsBlockHidden(int x, int y, int z, int face) const;
    
    bool drawLeft;
    bool drawRight;
    bool drawBottom;
    bool drawTop;
    bool drawBack;
    bool drawFront;
    
    glm::vec2 position;
    
private:
    std::vector<std::vector<std::vector<int>>> blocks;

    std::vector<GLfloat> meshVertexPositions;
    std::vector<GLfloat> meshTexCoords;
    std::vector<GLfloat> meshShadingValues;
    std::vector<GLuint> meshIndices;
    

    Texture dirtTex = Texture("textures/dirt.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture stoneTex = Texture("textures/cobblestone.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    Texture grassTex = Texture("textures/grass.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    
    VAO vao;

    void GenerateMesh();
};

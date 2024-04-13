#pragma once

#include <glad/glad.h>
#include <vector>

#include "World.h"
#include "Numbers.h"

#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16
#define CHUNK_LENGTH 16

class Chunk
{
public:
    Chunk(int xPos, int yPos);
    ~Chunk();

    void AddBlock();
    void DrawChunk();
    
private:
    std::vector<BlockType> blocks;
    VAO vao;
    VBO vertVBO;
    VBO texVBO;
    VBO shadingVBO;
    EBO ebo;

    void CollectData();
};

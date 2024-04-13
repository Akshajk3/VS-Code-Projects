#pragma once 

#include <unordered_map>
#include <vector>
#include <string>

#include <glad/glad.h>

#include "Numbers.h"
#include "Texture.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Shader.h"

class BlockType
{
public:
    BlockType(int xPos, int yPos, int zPos, Texture tex, Shader shader);
    ~BlockType();
    
    void Draw();
    void Delete();

private:
    std::string name;
    std::vector<GLfloat> vertexPositions;
    std::vector<GLfloat> texCoords;
    std::vector<GLfloat> shadingValues;
    Texture texture;
    Numbers numbers;
    Shader shaderProgram;
    VAO vao;
    VBO vertVBO;
    VBO texVBO;
    VBO shadingVBO;
    EBO ebo;
};

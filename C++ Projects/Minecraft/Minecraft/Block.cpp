#include "Block.h"

BlockType::BlockType(int xPos, int yPos, int zPos, Texture tex, Shader shader)
    : texture(tex), shaderProgram(shader), vertVBO(numbers.vertices), texVBO(numbers.texCoords), shadingVBO(numbers.shadingValues), ebo(numbers.indices, sizeof(numbers.indices))
{
    vertexPositions = numbers.vertices;
    texCoords = numbers.texCoords;
    shadingValues = numbers.shadingValues;
    
    for (int i = 0; i < vertexPositions.size(); i+=3)
    {
        vertexPositions[i] += xPos;
        vertexPositions[i + 1] += yPos;
        vertexPositions[i + 2] += zPos;
    }
    
    vao.Bind();
    
    vertVBO = VBO(vertexPositions);
    texVBO = VBO(texCoords);
    shadingVBO = VBO(shadingValues);
    
    ebo = EBO(numbers.indices, sizeof(numbers.indices));
    
    vao.LinkAttrib(vertVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    vao.LinkAttrib(texVBO, 1, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
    vao.LinkAttrib(shadingVBO, 2, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);
    
    vao.Unbind();
    vertVBO.Unbind();
    texVBO.Unbind();
    shadingVBO.Unbind();
    ebo.Unbind();
}

BlockType::~BlockType()
{
    
}

void BlockType::Draw()
{
    shaderProgram.Activate();
    texture.Bind();
    vao.Bind();
    glDrawElements(GL_TRIANGLES, sizeof(numbers.indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void BlockType::Delete()
{
    vao.Delete();
    vertVBO.Delete();
    texVBO.Delete();
    shadingVBO.Delete();
    ebo.Delete();
    texture.Delete();
    shaderProgram.Delete();
}

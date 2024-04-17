#include "Block.h"

BlockType::BlockType(glm::vec3 position)
    : vertVBO(numbers.vertices), texVBO(numbers.texCoords), shadingVBO(numbers.shadingValues), ebo(numbers.indices)
{
    std::vector<GLfloat> vertexData;
    int index = 0;

    for (int face = 0; face < 6; ++face) {
        for (int i = 0; i < 6; ++i) {
            // Define vertices for each face
            glm::vec3 v0, v1, v2, v3;
            switch (face) {
            case 0: // Top face
                v0 = glm::vec3(0, 1, 0) + position;
                v1 = glm::vec3(1, 1, 0) + position;
                v2 = glm::vec3(1, 1, 1) + position;
                v3 = glm::vec3(0, 1, 1) + position;
                break;
            case 1: // Bottom face
                v0 = glm::vec3(0, 0, 1) + position;
                v1 = glm::vec3(1, 0, 1) + position;
                v2 = glm::vec3(1, 0, 0) + position;
                v3 = glm::vec3(0, 0, 0) + position;
                break;
            case 2: // Right face
                v0 = glm::vec3(1, 0, 0) + position;
                v1 = glm::vec3(1, 1, 0) + position;
                v2 = glm::vec3(1, 1, 1) + position;
                v3 = glm::vec3(1, 0, 1) + position;
                break;
            case 3: // Left face
                v0 = glm::vec3(0, 0, 1) + position;
                v1 = glm::vec3(0, 1, 1) + position;
                v2 = glm::vec3(0, 1, 0) + position;
                v3 = glm::vec3(0, 0, 0) + position;
                break;
            case 4: // Back face
                v0 = glm::vec3(0, 0, 0) + position;
                v1 = glm::vec3(0, 1, 0) + position;
                v2 = glm::vec3(1, 1, 0) + position;
                v3 = glm::vec3(1, 0, 0) + position;
                break;
            case 5: // Front face
                v0 = glm::vec3(1, 0, 1) + position;
                v1 = glm::vec3(1, 1, 1) + position;
                v2 = glm::vec3(0, 1, 1) + position;
                v3 = glm::vec3(0, 0, 1) + position;
                break;
            }

            // Add vertices to vertexData
            index = addData(vertexData, index, v0, v1, v2, v0, v2, v3);
        }
    }
    
    vao.Bind();
    
    vertVBO = VBO(vertexPositions);
    texVBO = VBO(texCoords);
    shadingVBO = VBO(shadingValues);
    
    ebo = EBO(numbers.indices);
    
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
    vertexPositions.clear();
    vertexPositions.shrink_to_fit(); // Reduce the capacity to match the size
    texCoords.clear();
    texCoords.shrink_to_fit();
    shadingValues.clear();
    shadingValues.shrink_to_fit();
    vao.Delete();
    vertVBO.Delete();
    texVBO.Delete();
    shadingVBO.Delete();
    ebo.Delete();
}

void BlockType::Draw()
{
    vao.Bind();
    glDrawElements(GL_TRIANGLES, numbers.indices.size(), GL_UNSIGNED_INT, 0);
}

void BlockType::Delete() {
    vertexPositions.clear();
    vertexPositions.shrink_to_fit(); // Reduce the capacity to match the size
    texCoords.clear();
    texCoords.shrink_to_fit();
    shadingValues.clear();
    shadingValues.shrink_to_fit();
    vao.Delete();
    vertVBO.Delete();
    texVBO.Delete();
    shadingVBO.Delete();
    ebo.Delete();
}


std::vector<GLfloat> BlockType::getVertexPositions()
{
    return vertexPositions;
}

std::vector<GLfloat> BlockType::getTexCoords()
{
    return texCoords;
}

std::vector<GLfloat> BlockType::getShadingValues()
{
    return shadingValues;
}

int BlockType::addData(std::vector<GLfloat>& vertexData, int index, glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
    // Add vertex positions to vertex data
    vertexData[index++] = v0.x;
    vertexData[index++] = v0.y;
    vertexData[index++] = v0.z;
    vertexData[index++] = v1.x;
    vertexData[index++] = v1.y;
    vertexData[index++] = v1.z;
    vertexData[index++] = v2.x;
    vertexData[index++] = v2.y;
    vertexData[index++] = v2.z;
    vertexData[index++] = v0.x;
    vertexData[index++] = v0.y;
    vertexData[index++] = v0.z;
    vertexData[index++] = v2.x;
    vertexData[index++] = v2.y;
    vertexData[index++] = v2.z;
    vertexData[index++] = v3.x;
    vertexData[index++] = v3.y;
    vertexData[index++] = v3.z;
    return index;
}
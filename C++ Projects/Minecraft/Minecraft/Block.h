#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "Numbers.h"


class Block
{
public:
    Block(glm::vec3 position);

private:
    glm::vec3 blockPos;

    std::vector<GLfloat> blockVertexPositons;
    std::vector<GLfloat> blockTexCoords;
    std::vector<GLfloat> blockShadingValues;
    std::vector<GLuint> meshIndices;
};
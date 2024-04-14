#pragma once

#include <glad/glad.h>
#include <vector>

struct Numbers
{
    std::vector<GLfloat> vertices = {
         // Front face
         -0.5f, -0.5f,  0.5f,
          0.5f, -0.5f,  0.5f,
          0.5f,  0.5f,  0.5f,
         -0.5f,  0.5f,  0.5f,

        // Back face
        -0.5f,  -0.5f, -0.5f,
         0.5f,  -0.5f, -0.5f,
         0.5f,   0.5f, -0.5f,
        -0.5f,   0.5f, -0.5f,

        // Top face
        -0.5f,   0.5f,  0.5f,
         0.5f,   0.5f,  0.5f,
         0.5f,   0.5f, -0.5f,
        -0.5f,   0.5f, -0.5f,

        // Bottom face
        -0.5f,  -0.5f,  0.5f,
         0.5f,  -0.5f,  0.5f,
         0.5f,  -0.5f, -0.5f,
        -0.5f,  -0.5f, -0.5f,

        // Right face
         0.5f,  -0.5f,  0.5f,
         0.5f,  -0.5f, -0.5f,
         0.5f,   0.5f, -0.5f,
         0.5f,   0.5f,  0.5f,

        // Left face
        -0.5f,  -0.5f,  0.5f,
        -0.5f,  -0.5f, -0.5f,
        -0.5f,   0.5f, -0.5f,
        -0.5f,   0.5f,  0.5f,
    };
    
    std::vector<GLfloat> texCoords = {
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
    };
    
    std::vector<GLfloat> shadingValues = {
        0.6, 0.6, 0.6, 0.6,
        0.6, 0.6, 0.6, 0.6,
        0.6, 0.6, 0.6, 0.6,
        0.6, 0.6, 0.6, 0.6,


        0.6, 0.6, 0.6, 0.6,
        0.6, 0.6, 0.6, 0.6,
        0.6, 0.6, 0.6, 0.6,
        0.6, 0.6, 0.6, 0.6,


        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 1.0,


        0.4, 0.4, 0.4, 0.4,
        0.4, 0.4, 0.4, 0.4,
        0.4, 0.4, 0.4, 0.4,
        0.4, 0.4, 0.4, 0.4,


        0.8, 0.8, 0.8, 0.8,
        0.8, 0.8, 0.8, 0.8,
        0.8, 0.8, 0.8, 0.8,
        0.8, 0.8, 0.8, 0.8,


        0.8, 0.8, 0.8, 0.8,
        0.8, 0.8, 0.8, 0.8,
        0.8, 0.8, 0.8, 0.8,
        0.8, 0.8, 0.8, 0.8,
    };
    
    // Indices for vertices order
    GLuint indices[36] = {
        0, 1, 2, 2, 3, 0, // Front face
        4, 5, 6, 6, 7, 4, // Back face
        8, 9, 10, 10, 11, 8, // Top face
        12, 13, 14, 14, 15, 12, // Bottom face
        16, 17, 18, 18, 19, 16, // Right face
        20, 21, 22, 22, 23, 20  // Left face
    };
};
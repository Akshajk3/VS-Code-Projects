#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "ShaderManager.h"

class Texture
{
public:
    GLuint ID;
    GLenum type;
    Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);
    
    void TexUnit(ShaderManager& shader, const char* uniform, GLuint unit);
    void Bind();
    
};

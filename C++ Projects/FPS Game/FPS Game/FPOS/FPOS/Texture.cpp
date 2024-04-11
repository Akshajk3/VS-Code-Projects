#include "Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    texType = texType;
    
    int imgWidth, imgHeight, numColCh;
    
    stbi_set_flip_vertically_on_load(true);
    
    unsigned char* bytes = stbi_load(image, &imgWidth, &imgHeight, &numColCh, 0);
    
    glGenTextures(1, &ID);
    
    glActiveTexture(slot);
    glBindTexture(texType, ID);
    
    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    
}

void Texture::TexUnit(ShaderManager &shader, const char *uniform, GLuint unit)
{
    
}

void Texture::Bind()
{
    
}

void Texture::Unbind()
{
    
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}

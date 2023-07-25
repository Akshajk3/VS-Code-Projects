#ifndef TEXTURE_MANAGER_CLASS_H
#define TEXTURE_MANAGER_CLASS_H

#include <array>
#include <string>
#include <stb/stb_image.h>

#include "shader.h"
#include "texture_array.h"

constexpr uint32_t TEX_ARRAY_SIZE = 32;
struct Image
{
    GLubyte* image_data;
    GLsizei width, height;
    GLint comp;
};

class TextureManager
{
    ShaderProgram* shaderProgram;
    Image texture_images[TEX_ARRAY_SIZE];
    TextureArray texture_array;
    GLubyte sampler_location;
    mutable uint32_t current_index;
public:
    TextureManager(size_t texture_width, size_t texture_height, ShaderProgram* shader_program);
    ~TextureManager();
    void addTexture(const std::string& texture_path);

    void generateMipmaps() const
    {
        texture_array.generateMipmaps();
    }
    void activate() const
    {
        texture_array.activate();
        shaderProgram->setUniform1i(sampler_location, 0);
    }
    uint32_t getCurrentIndex() const
    {
        return current_index;
    }
};

#endif
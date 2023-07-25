#include "textureManager.h"

TextureManager::TextureManager(size_t texture_width, size_t texture_height, ShaderProgram* shaderProgram)
    :texture_array(texture_width, texture_height, TEX_ARRAY_SIZE, true, GL_NEAREST_MIPMAP_LINEAR),
    texture_images(), shaderProgram(shaderProgram), current_index(0u)
{
    sampler_location = shaderProgram->findUniform("texture_array_sampler");
    stbi_set_flip_vertically_on_load(true);
}

TextureManager::~TextureManager()
{

}

void TextureManager::addTexture(const std::string& texture_path)
{
    Image* texture_image = texture_images + (current_index % TEX_ARRAY_SIZE);
    texture_image->image_data = stbi_load(texture_path.c_str(), &texture_image->width, &texture_image->height, &texture_image->comp, 0);
    texture_array.bind();
    texture_array.addTextureData(texture_image->width, texture_image->height, current_index, texture_image->image_data);
    stbi_image_free(texture_image->image_data);
    current_index++;

}
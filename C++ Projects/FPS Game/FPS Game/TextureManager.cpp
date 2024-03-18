#include "TextureManager.h"

TextureManager::TextureManager(const char* image_path, GLenum tex_type, GLenum slot, GLenum format, GLenum pixelType)
{
	type = tex_type;

	int imgWidth, imgHeight, numColCh;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(image_path, &imgWidth, &imgHeight, &numColCh, 0);

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(tex_type, ID);

	glTexParameteri(tex_type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(tex_type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(tex_type, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(tex_type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(tex_type, 0, GL_RGBA, imgWidth, imgHeight, 0, format, pixelType, bytes);
	glGenerateMipmap(tex_type);

	stbi_image_free(bytes);
	glBindTexture(tex_type, 0);
}

void TextureManager::texUnit(ShaderManager& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void TextureManager::Bind()
{
	glBindTexture(type, ID);
}

void TextureManager::Unbind()
{
	glBindTexture(type, 0);
}

void TextureManager::Delete()
{
	glDeleteTextures(1, &ID);
}
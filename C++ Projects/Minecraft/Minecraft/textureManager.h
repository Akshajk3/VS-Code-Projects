#ifndef TEXTURE_MANAGER_CLASS_H
#define TEXTURE_MANAGER_CLASS_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <string>
#include <array>

#include "shaderClass.h"

class TextureManager
{
	const uint32_t TEX_ARRAY_SIZE = 32;

	struct Image
	{
		GLubyte* iamge_data;
		GLsizei width, height;
		GLint comp;
	};

public:
	GLuint ID;
	GLenum type;
	TextureManager(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void addTexture(const std::string& texture_path);
	void Bind();
	void Unbind();
	void Delete();
};

#endif // !TEXTURE_MANAGER_CLASS_H

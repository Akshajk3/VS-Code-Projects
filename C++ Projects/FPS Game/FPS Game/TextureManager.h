#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "ShaderManager.h"

class TextureManager
{
public:
	TextureManager(const char* image_path, GLenum tex_type, GLenum slot, GLenum format, GLenum pixelType);

	GLuint ID;
	GLuint type;

	void texUnit(ShaderManager& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};
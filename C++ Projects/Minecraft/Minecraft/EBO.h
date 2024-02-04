#pragma once

#include <glad/glad.h>

class EBO
{
public:

	EBO(GLuint* indices, GLsizeiptr size);

	GLuint ID;

	void Bind();
	void Unbind();
	void Delete();
};
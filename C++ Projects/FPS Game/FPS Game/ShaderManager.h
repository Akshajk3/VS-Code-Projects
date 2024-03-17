#pragma once

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>

class ShaderManager
{
public:
	GLuint ID;
	ShaderManager(const char* vertexFile, const char* fragmentFile);

	void Activate();
	void Delete();
private:
	void compileErrors(unsigned int shader, const char* type);
};
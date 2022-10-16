#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>

class EBO
{
public:
	//Reference ID for the Element Buffer Object
	GLuint ID;
	//Constructor that generates a Element Buffer Object and links it to the indices
	EBO(GLuint* indices, GLsizeiptr size);

	//Binds the EBO
	void Bind();
	//Unbinds the EBO
	void Unbind();
	//Deletes the EBO
	void Delete();
};

#endif
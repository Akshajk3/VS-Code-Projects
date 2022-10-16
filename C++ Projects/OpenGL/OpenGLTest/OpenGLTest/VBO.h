#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
	public:
		//Reference ID for the Vertex Buffer Object
		GLuint ID;
		//Constructor that generates a Vertex Buffer Object and links it to the vertices
		VBO(GLfloat* verticies, GLsizeiptr size);
		//Binds the VBO
		void Bind();
		//Unbinds the VBO
		void Unbind();
		//Deletes the VBO
		void Delete();
};

#endif
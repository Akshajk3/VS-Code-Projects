#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "VBO.h"

class VAO
{
	public:
		//Reference ID for the Vertex Array Object
		GLuint ID;
		//Constructor that generates the Vertex Array Object ID
		VAO();

		//Links the VBO to the VAO using a certain layout
		void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr string);
		//Binds the VAO
		void Bind();
		//Unbinds the VAO
		void Unbind();
		//Deletes the VAO
		void Delete();
};

#endif
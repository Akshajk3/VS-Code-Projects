#include "Cube.h"

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /			TexCoord		//
	 0.5f,  0.5f,  0.5f,      1.0f, 0.0f, 0.0f,			0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,      0.0f, 1.0f, 0.0f,			0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,      0.0f, 0.0f, 1.0f,			1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,      1.0f, 1.0f, 1.0f,			1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,      1.0f, 0.0f, 0.0f,			0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,      0.0f, 1.0f, 0.0f,			0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,      0.0f, 0.0f, 1.0f,			1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,      1.0f, 1.0f, 1.0f,			1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,      1.0f, 0.0f, 0.0f,			0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,      0.0f, 1.0f, 0.0f,			0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,      0.0f, 0.0f, 1.0f,			1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,      1.0f, 1.0f, 1.0f,			1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,      1.0f, 0.0f, 0.0f,			0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,      0.0f, 1.0f, 0.0f,			0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,      0.0f, 0.0f, 1.0f,			1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,      1.0f, 1.0f, 1.0f,			1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,      1.0f, 0.0f, 0.0f,			0.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,      0.0f, 1.0f, 0.0f,			0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,      0.0f, 0.0f, 1.0f,			1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,      1.0f, 1.0f, 1.0f,			1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,      1.0f, 0.0f, 0.0f,			0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,      0.0f, 1.0f, 0.0f,			0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,      0.0f, 0.0f, 1.0f,			1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,      1.0f, 1.0f, 1.0f,			1.0f, 0.0f
};


// Indices for vertices order
GLuint indices[] =
{
	 0,  1,  2,  0,  2,  3,
	 4,  5,  6,  4,  6,  7,
	 8,  9, 10,  8, 10, 11,
	12, 13, 14, 12, 14, 15,
	16, 17, 18, 16, 18, 19,
	20, 21, 22, 20, 22, 23
};


void Cube::Init(const Window& window, glm::vec3 position)
{
	Position = position;

	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));
	
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	texture.texUnit(shaderProgram, "tex0", 0);
}


void Cube::Update()
{
	shaderProgram.Activate();

	glm::mat4 view = glm::mat4(1.0);
	view = glm::translate(view, Position);
	int viewLoc = glGetUniformLocation(shaderProgram.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	texture.Bind();
	VAO1.Bind();
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void Cube::Destroy()
{
	VAO1.Delete();
	shaderProgram.Delete();
	texture.Delete();
}

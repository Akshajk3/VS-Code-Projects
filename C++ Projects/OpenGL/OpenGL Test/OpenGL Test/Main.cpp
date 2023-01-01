#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL to use
	// Here we are using OpenGL Version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Define the vertices that are used for rendering the triangle
	GLfloat vertices[] =
	{ //               COORDINATES                  /     COLORS           //
		-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.09f, 0.35f,  0.61f, // Lower left corner
		 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.09f, 0.35f,  0.61f, // Lower right corner
		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     0.26f, 0.80f,  0.63f, // Upper corner
		-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.17f, 0.56f,  0.62f, // Inner left
		 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.17f, 0.56f,  0.62f, // Inner right
		 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.09f, 0.35f,  0.61f  // Inner down
	};

	// Define the indeces for the EBO
	GLuint  indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};

	// Create the window and make sure it initialized properly
	GLFWwindow* window = glfwCreateWindow(800, 800, "Test Window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "L + RATIO + BOZO, Window failed to init" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Add the window to the current context
	glfwMakeContextCurrent(window);

	// Initialize glad
	gladLoadGL();

	// Create the viewport of OpenGL in the Window
	// Here the view port goes from x = 0, y = 0 to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// Generates Shader object using shaders defualt.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");

	// Generate the VAO and bind it
	VAO VAO1;
	VAO1.Bind();

	// Generate the VBO and link it to the vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generate the EBO and link it to the indices
	EBO EBO1(indices, sizeof(indices));

	// Links the VBO attributes such as the vertex positions and colors to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// Unbind all to prevent acidentally modifying
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniId = glGetUniformLocation(shaderProgram.ID, "scale");

	// The main loop that runs while the window is still open
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.2f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL what Shader Program we want to use
		shaderProgram.Activate();
		// Assigns a value to the uniform; NOTE: must always come after the shader program has been activated
		glUniform1f(uniId, 0.5f);
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw the triangle using GL_TRIANGES as a primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		// Swap the front and back buffers
		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	// Delete the window object before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}
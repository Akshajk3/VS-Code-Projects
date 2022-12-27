#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


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
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
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



	// The main loop that runs while the window is still open
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		// Draw the triangle using GL_TRIANGES as a primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete the window object before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}
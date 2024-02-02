#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <iostream>

int main(int argc, char* argv)
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(1024, 512, "Raycaster", NULL, NULL);
	if (window == nullptr)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 1024, 512);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.3, 0.3, 0.3, 0);
		glOrtho(0, 1024, 512, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
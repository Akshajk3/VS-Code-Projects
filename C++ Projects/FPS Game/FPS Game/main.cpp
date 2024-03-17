#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLfloat vertices[] =
{
	-0.5f, -0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
};

GLuint indices[] =
{
	0, 2, 1,
	0, 3, 2
};


int main()
{
	if (!glfwInit())
	{
		std::cout << "Failed to Init glfw" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(1280, 720, "FPS Game", NULL, NULL);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, 1280, 720);
	
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
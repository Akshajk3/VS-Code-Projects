#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f
};

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Minecraft Vindle Edition", NULL, NULL);
	if (window == nullptr)
	{
		std::cout << "Failed to create Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	gladLoadGL();

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.27f, 0.67f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Terraria Vindle Edition", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 600);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
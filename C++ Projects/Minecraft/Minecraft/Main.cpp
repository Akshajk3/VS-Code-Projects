#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Camera.h"
#include "textureManager.h"
#include "block_type.h"
#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

const int windowWidth = 1280;
const int windowHeight = 720;
const char* windowName = "Minecraft Vindle Edition";

int main(void)
{
	glfwInit();

	if (!glfwInit())
	{
		std::cout << "GLFW Failed to Init" << std::endl;
		glfwTerminate();
		return -1;
	}

	Window* window = Window::createWindow(windowWidth, windowHeight, windowName);
	if (window == nullptr)
	{
		std::cout << "Failed to Create Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	gladLoadGL();

	glViewport(0, 0, windowWidth, windowHeight);

	Shader shaderProgram("default.vert", "default.frag");
	
	glEnable(GL_DEPTH_TEST);

	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window->window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window->window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		glfwSwapBuffers(window->window);
		glfwPollEvents();

	}

	Window::freeWindow(window);
	glfwTerminate();
	return 0;
}
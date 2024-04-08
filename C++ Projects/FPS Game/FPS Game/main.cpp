#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>

#include "ShaderManager.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "TextureManager.h"
#include "Camera.h"

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;

int main()
{
	if (!glfwInit())
	{
		std::cout << "Failed to Init glfw" << std::endl;
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "FPS Game", NULL, NULL);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, WIN_WIDTH, WIN_HEIGHT);
    
    ShaderManager shaderProgram("vert.glsl", "frag.glsl");
    
    VAO VAO1;
    VAO1.Bind();
    
    VBO VBO1(vertices, sizeof(vertices));
    
    EBO EBO1(indices, sizeof(indices));
    
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    std::string texPath = "pop_cat.png";

    TextureManager popCat(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    glEnable(GL_DEPTH_TEST);

    Camera camera(WIN_WIDTH, WIN_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));
    
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();

        camera.Input(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        popCat.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    popCat.Delete();
    shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

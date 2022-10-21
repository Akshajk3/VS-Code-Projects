#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "shaderClass.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"





int main()
{
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(800, 800, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);
	
		// Vertices coordinates
	GLfloat vertices[] =
	{ //			Coordinates					/			Colors		  //
		-0.5f, -0.5f * float(sqrt(3)) / 3,		 0.0f,	0.8f, 0.3f, 0.02f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3,		 0.0f,	0.8f, 0.3f, 0.02f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3,	 0.0f,	1.0f, 0.6f, 0.32f, // Upper corner
		-0.25, 0.5f * float(sqrt(3)) / 6,		 0.0f,	0.9f, 0.45f, 0.17f,//Inner Left
		0.25f, 0.5f * float(sqrt(3)) / 6,		 0.0f,	0.9f, 0.45f, 0.17f,//Inner Right
		0.0f, -0.5f * float(sqrt(3)) / 3,		 0.0f,	0.8f, 0.3f, 0.02f, //Inner Down
	};

	GLuint indices[] =
	{
		0, 3, 5, //Lower Left Triangle
		3, 2, 4, //Lower Right Triangle
		5, 4, 1 //Upper Triangle
	};

	//Generate Shader object using shaders defualt.vert, and default.frag
	Shader ShaderProgram("default.vert", "default.frag");

	//Generate the Vertex Array Object
	VAO VAO1;
	VAO1.Bind();

	//Generate the Vertex Buffer Object and link it to the vertices
	VBO VBO1(vertices, sizeof(vertices));
	//Generate the Element Buffer Object and link it to the indices
	EBO EBO1(indices, sizeof(indices));

	//Links the VAO to the VBO
	VAO1.LinkVBO(VBO1, 0);
	//Unbind all to prevent acidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();





	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO, EBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		ShaderProgram.Activate();
			// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	ShaderProgram.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
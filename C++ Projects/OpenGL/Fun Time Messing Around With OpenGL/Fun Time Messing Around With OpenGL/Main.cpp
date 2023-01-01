#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Source code for the vertex shader
const char* vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

// Source code for the fragment shader
const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
	// Initalize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL to use
	// In this case we are using OpenGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Define the vertices that will be used for the triangle
	GLfloat vertices[] =
	{
		-0.5f, 0.5f, 0.0f,  // Upper Left Corner
		-0.5f, -0.5f, 0.0f, // Lower Left Corner
		 0.0f, 0.5f, 0.0f,	// Upper Right Corner
		 0.05f, 0.5f, 0.0f  // Lower Right Corner
	};

	GLuint indices[] =
	{
		0, 1, 2,
		3, 2, 1
	};

	// Initialize the window and make sure it initalzed properly
	GLFWwindow* window = glfwCreateWindow(800, 800, "Fun Messing Around With OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "BOZO BOZO ur window did not init properly" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Bring the window into the current context
	glfwMakeContextCurrent(window);

	// Initialize glad
	gladLoadGL();

	// Create the glad viewport in the window
	// Here the viewport goes from x = 0, y = 0 to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	// Create Vertex Shader and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attatch the vertex shader source code to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the vertex shader into machine code
	glCompileShader(vertexShader);

	// Create the Fragment Shader object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// Attatch the Fragment Shader source code to the Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Fragment Shader into machine code
	glCompileShader(fragmentShader);

	// Create the Shader Program and get its reference
	GLuint shaderProgram = glCreateProgram();
	// Attatch the vertex and fragment shaders to the Shader Program Object
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// Link all the shaders together into the Shader Program
	glLinkProgram(shaderProgram);

	// Delete the Vertex and Fragement Shader objects because they are no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Create reference containers for the VAO and VBO
	GLuint VAO, VBO, EBO;

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO by specifying it is a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	// Configure the Vertex	Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind the both the VAO and VBO to 0 so that we don't accidentally modify the VAO and VBO that we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		// Clear the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which shader program we want to use
		glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		// Draw the triangle using GL_TRIANGLES as the primitive
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// Swap the front and back buffers
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we have created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	// Delete the window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = {
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0)\n"
    "}\0"
};

const char* fragmentShaderSource = {
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0);\n"
    "}\0"
};

int main()
{
    // Initialze GLFW
    glfwInit();
    
    // Tell GLFW what version of OpenGL is being used
    // In this case we are using OpenGL version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW to use the Core Profile
    // This means we are only using the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] = {
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
    };

    // Create the window of 800 by 800, and name it Test Window
    GLFWwindow* window = glfwCreateWindow(800, 800, "Test Window", NULL, NULL);

    // Check that the window Initialized properly
    if(window == NULL)
    {
        std::cout << "Window failed to Init! L + Ratio + Bozo" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Introduce the window into the current OpenGL context
    glfwMakeContextCurrent(window);

    // Load GLAD so that it is configured with OpenGL
    gladLoadGL();

    // Specify the viewport of OpenGL in the window
    // In this case the viewport is located at 0,0 and has a size of 800 by 800
    glViewport(0, 0, 800, 800);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // Specify the color of the background
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    // Swap the front and back buffers
    glfwSwapBuffers(window);

    // The main loop
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }


    // Destroy the window object
    glfwDestroyWindow(window);
    // Terminate OpenGL
    glfwTerminate();
    return 0;
}
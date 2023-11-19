#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

GLfloat vertices[] =
{
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower Left Corner
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower Right Corner
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper Corner
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Innter Left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

GLuint indices[] =
{
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
};

int main()
{
    glfwInit();

    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    
    Shader shaderProgram("vert.glsl", "frag.glsl");
    
    GLuint VBO, VAO, EBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

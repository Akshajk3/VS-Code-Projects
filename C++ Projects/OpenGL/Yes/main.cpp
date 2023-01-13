#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 800, "Yes Window", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "The Window Failed to Init" << std::endl;
    }
}
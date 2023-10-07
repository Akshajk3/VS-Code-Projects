#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main(int argc, char* argv[])
{
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 800, "Minecraft Vindle Edition", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    gladLoadGL();
    
    glViewport(0, 0, 800, 800);
    
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.27f, 0.67f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    return 0;
}

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"
#include "Numbers.h"
#include "Block.h"
#include "Chunk.h"

const unsigned int width = 1920;
const unsigned int height = 1080;

Camera camera(width, height, glm::vec3(16.0f, 20.0f, 40.0f));

void errorCallback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

void resizeWindowCallback(GLFWwindow* window, int newWidth, int newHeight)
{
    glViewport(0, 0, newWidth, newHeight);
}

void windowFocusCallback(GLFWwindow* window, int focused)
{
    if (focused)
    {
        camera.CaptureMouse(window);
    }
    else
    {
        camera.ReleaseMouse(window);
    }
}

int main()
{
    glfwSetErrorCallback(errorCallback);
    
    if(!glfwInit())
    {
        std::cout << "Failed to Init GLFW" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Vindelcraft", NULL, NULL);

    if (window == nullptr)
    {
        std::cout << "Failed to create Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, resizeWindowCallback);
    glfwSetWindowFocusCallback(window, windowFocusCallback);

    glfwMakeContextCurrent(window);

    gladLoadGL();
    
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    
    int frameWidth, frameHeight;
    
    glfwGetWindowSize(window, &frameWidth, &frameHeight);

    glViewport(0, 0, width, height);

    Shader shaderProgram("vert.glsl", "frag.glsl");

    std::string texPath = "textures/grass.png";

    Texture grassTex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    grassTex.texUnit(shaderProgram, "tex0", 0);

    glEnable(GL_DEPTH_TEST);

    std::vector<Chunk> world;

    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            world.push_back(Chunk(glm::vec2(x, y)));
        }
    }

    Chunk chunk(glm::vec2(0, 0));
    Chunk chunk1(glm::vec2(1, 1));
    
    glfwSetWindowSize(window, width + 1, height + 1);
    glfwSetWindowSize(window, width, height);

    // glfwSwapInterval is used to turn on and off Vsync
    // 0 = off, 1 = on
    glfwSwapInterval(0);
      
    double lastTime = glfwGetTime();
    int frame = 0;
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        shaderProgram.Activate();

        for (auto& chunk : world)
        {
            chunk.DrawChunk();
        }

        double currentTime = glfwGetTime();
        frame++;

        if (currentTime - lastTime >= 1)
        {
            char title[255];
            snprintf(title, sizeof(title), "Vindelcraft: FPS: %i", frame);
            glfwSetWindowTitle(window, title);
            frame = 0;
            lastTime = currentTime;
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    for (auto& chunk : world)
    {
        chunk.DeleteChunk();
    }

    grassTex.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

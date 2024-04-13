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

const unsigned int width = 1280;
const unsigned int height = 720;

void errorCallback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
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

    glfwMakeContextCurrent(window);

    gladLoadGL();
    
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    
    int frameWidth, frameHeight;
    
    glfwGetWindowSize(window, &frameWidth, &frameHeight);

    glViewport(0, 0, width, height);

    Shader shaderProgram("vert.glsl", "frag.glsl");

    std::string texPath = "textures/cobblestone.png";

    Texture grassTex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    grassTex.texUnit(shaderProgram, "tex0", 0);

    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
    
    std::vector <BlockType> chunk;
    
    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            for (int z = 0; z < 8; z++)
            {
                chunk.push_back(BlockType(x, y, z, grassTex, shaderProgram));
            }
        }
    }
    
    glfwSetWindowSize(window, width + 1, height + 1);
    glfwSetWindowSize(window, width, height);

    //glfwSwapInterval(0);
      
    double lastTime = glfwGetTime();
    int frame = 0;
    
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");
        
        for (auto& block : chunk)
        {
            block.Draw();
        }

        double currentTime = glfwGetTime();
        frame++;

        if (currentTime - lastTime >= 1)
        {
            std::cout << frame << std::endl;
            frame = 0;
            lastTime = currentTime;
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    for (auto& block : chunk)
    {
        block.Delete();
    }
    
    grassTex.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

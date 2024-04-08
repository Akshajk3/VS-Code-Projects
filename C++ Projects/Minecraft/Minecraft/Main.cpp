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

const unsigned int width = 1280;
const unsigned int height = 720;

// Vertices coordinates
GLfloat vertices[] = {
    // Front face
    -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    // Back face
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    // Top face
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    // Bottom face
    -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    // Right face
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    // Left face
    -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

// Indices for vertices order
GLuint indices[] = {
    0, 1, 2, 2, 3, 0, // Front face
    4, 5, 6, 6, 7, 4, // Back face
    8, 9, 10, 10, 11, 8, // Top face
    12, 13, 14, 14, 15, 12, // Bottom face
    16, 17, 18, 18, 19, 16, // Right face
    20, 21, 22, 22, 23, 20  // Left face
};

void errorCallback(int error, const char* description) {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

std::vector<GLfloat> createCubeVertices(glm::vec3 position) {
    std::vector<GLfloat> cubeVertices = {
        // Front face
        -0.5f + position.x, -0.5f + position.y, 0.5f + position.z, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f + position.x, -0.5f + position.y, 0.5f + position.z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f + position.x, 0.5f + position.y, 0.5f + position.z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f + position.x, 0.5f + position.y, 0.5f + position.z, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        // Back face
        -0.5f + position.x, -0.5f + position.y, -0.5f + position.z, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f + position.x, -0.5f + position.y, -0.5f + position.z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f + position.x, 0.5f + position.y, -0.5f + position.z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f + position.x, 0.5f + position.y, -0.5f + position.z, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        // Top face
        -0.5f + position.x, 0.5f + position.y, 0.5f + position.z, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f + position.x, 0.5f + position.y, 0.5f + position.z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f + position.x, 0.5f + position.y, -0.5f + position.z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f + position.x, 0.5f + position.y, -0.5f + position.z, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        // Bottom face
        -0.5f + position.x, -0.5f + position.y, 0.5f + position.z, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f + position.x, -0.5f + position.y, 0.5f + position.z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f + position.x, -0.5f + position.y, -0.5f + position.z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f + position.x, -0.5f + position.y, -0.5f + position.z, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        // Right face
        0.5f + position.x, -0.5f + position.y, 0.5f + position.z, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f + position.x, -0.5f + position.y, -0.5f + position.z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f + position.x, 0.5f + position.y, -0.5f + position.z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f + position.x, 0.5f + position.y, 0.5f + position.z, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
        // Left face
        -0.5f + position.x, -0.5f + position.y, 0.5f + position.z, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f + position.x, -0.5f + position.y, -0.5f + position.z, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f + position.x, 0.5f + position.y, -0.5f + position.z, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f + position.x, 0.5f + position.y, 0.5f + position.z, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };

    return cubeVertices;
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
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

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

    glViewport(0, 0, width, height);

    Shader shaderProgram("vert.glsl", "frag.glsl");

    VAO vao;
    vao.Bind();

    std::vector<GLfloat> allVertices;
    std::vector<GLuint> allIndices;
    std::vector<glm::vec3> cubePositions = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 0.0f, -2.0f),
        glm::vec3(-2.0f, 0.0f, -2.0f)
    };

    for (const auto& position : cubePositions)
    {
        auto cubeVertices = createCubeVertices(position);
        allVertices.insert(allVertices.end(), cubeVertices.begin(), cubeVertices.end());
        GLuint startIndex = allIndices.size();
        for (GLuint i = 0; i < 36; i++)
            allIndices.push_back(indices[i] + startIndex);
    }

    VBO vbo(allVertices.data(), allVertices.size() * sizeof(GLfloat));
    EBO ebo(allIndices.data(), allIndices.size() * sizeof(GLuint));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    std::string texPath = "textures/cobblestone.png";

    Texture grassTex(texPath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    grassTex.texUnit(shaderProgram, "tex0", 0);

    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shaderProgram.Activate();

        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        glUniform1f(uniID, 0.5f);
        grassTex.Bind();
        vao.Bind();

        for (size_t i = 0; i < cubePositions.size(); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)(36 * i * sizeof(GLuint)));
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    grassTex.Delete();
    shaderProgram.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

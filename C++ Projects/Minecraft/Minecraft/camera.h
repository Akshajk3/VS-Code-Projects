#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "player.h"
#include "shader.h"

class Camera
{
    Player* player;
    glm::mat4 proj, view, model, mvp;
    glm::vec3 input;
    GLubyte mvp_loc;
    ShaderProgram* shaderProgram;
public:
    size_t width, height;
    
    Camera(Player* player, ShaderProgram* shaderProgram, GLsizei width, GLsizei height)
        : player(player), shaderProgram(shaderProgram), input(0, 0, 0), proj(1.0f), view(1.0f),
        model(1.0f), width(width), height(height), mvp_loc()
        {
            proj = glm::perspective(glm::radians(70.0f), (float)width / height, 0.1f, 500.0f);
            view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
            model = glm::mat4(1.0f);
            mvp_loc = shaderProgram->findUniform("mvp");
        }
    ~Camera()
    {

    }

    void poll_input(const glm::vec3& tvec)
    {
        input += tvec;
    }
    void reset_input()
    {
        input = glm::vec3(0, 0, 0);
    }

    void update_dim(GLsizei width, GLsizei height)
    {
        this->width = width;
        this->height = height;
        proj = glm::perspective(glm::radians(70.0f), (float)width / height, 0.1f, 500.0f);
        std::cout << "Resized" << width << " * " << height << std::endl;
    }
    void update(float delta_time)
    {
        player->updatePos(input, delta_time);
        update_matrices();
        load_matrices();
    }
private:
    void update_matrices()
    {
        view = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        view = glm::rotate(view, -player->getPitch(), -glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::rotate(view, (-player->getYaw() - pi / 2), -glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, -player->getPos());
        mvp = proj * view * model;
    }
    void load_matrices()
    {
        shaderProgram->setUniformMat4f(mvp_loc, mvp);
    }
};

#endif
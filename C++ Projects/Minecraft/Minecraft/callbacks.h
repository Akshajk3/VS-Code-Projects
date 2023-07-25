#ifndef CALLBACKS_CLASS_H
#define CALLBACKS_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#include "player.h"
#include "hit.h"
#include "camera.h"
#include "world.h"

constexpr float sensitivity = 0.004;

inline void APIENTRY GLDebugMsgCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
    const char* _source;
    const char* _type;
    const char* _severity;

    switch(source)
    {
    case GL_DEBUG_SOURCE_API:
        _source = "API";
        break;
    
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM";
        break;
    
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        _source = "UNKOWN";
        break;
    default:
        _source = "UNKOWN";
        break;
    }
    switch(type)
    {
    case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRICATED BEHAVIOUR";
        break;
    case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        _type = "POP GROUP";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PROTABILITY";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        _type = "PUSH GROUP";
        break;
    case GL_DEBUG_TYPE_OTHER:
        _type = "MISCELLANEOUS";
        break;
    default:
        _type = "UNKOWN";
        break;
    }
    switch(severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION";
        break;
    default:
        _severity = "UNKOWN";
        break;
    }
    std::cout << "[GL DEBUG MESSAGE]: "
        << "ID " << id << ", "
        << _type << " message of "
        << _severity << " severity, from "
        << _source << ": \n" << msg << "\n";
}

static Player* playerptr = nullptr;
static Camera* cameraptr = nullptr;
static World* worldptr = nullptr;
static PlayerHitray* hitrayptr = nullptr;
static bool mouse_captured = false;
static float last_x_pos = 0.0f, last_y_pos = 0.0f;

inline void link_elements(Player* player, Camera* camera, World* world, PlayerHitray* hitray)
{
    playerptr = player;
    cameraptr = camera;
    worldptr = world;
    hitrayptr = hitray;
}

inline void on_mouse_press(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS && glfwGetWindowAttrib(window, GLFW_HOVERED))
    {
        switch(button)
        {
        case GLFW_MOUSE_BUTTON_LEFT:
            if(!mouse_captured)
            {
                mouse_captured = true;
                glfwSetCursorPos(window, (float)cameraptr->width / 2, (float)cameraptr->height / 2);
                last_x_pos = (float)cameraptr->width / 2;
                last_y_pos = (float)cameraptr->height / 2;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            }
            else
            {
                hitrayptr->update(playerptr->getYaw(), playerptr->getPitch(), playerptr->getPos());
                while(hitrayptr->distance < HIT_RANGE)
                {
                    if(hitrayptr->step())
                    {
                        worldptr->setBlock(hitrayptr->block, 0);
                        break;
                    }
                }
            }
            break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                if(mouse_captured)
                {
                    hitrayptr->update(playerptr->getYaw(), playerptr->getPitch(), playerptr->getPos());
                    while(hitrayptr->distance < HIT_RANGE)
                    {
                        if(hitrayptr->step())
                        {
                            worldptr->setBlock(hitrayptr->block, playerptr->holding);
                            break;
                        }
                    }
                }
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                if(mouse_captured)
                {
                    hitrayptr->update(playerptr->getYaw(), playerptr->getPitch(), playerptr->getPos());
                    while(hitrayptr->distance < HIT_RANGE)
                    {
                        playerptr->holding = worldptr->getBlock(hitrayptr->block);
                        break;
                    }
                }
                break;
        }
    }
}

inline void on_resize(GLFWwindow* window, GLsizei width, GLsizei height)
{
    cameraptr->update_dim(width, height);
    glViewport(0, 0, width, height);
    std::cout << "Resized to " << width << " * " << height << "\n"; 
}

inline void on_key_update(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    int dx, dy, dz;
    dx = 0, dy = 0, dz = 0;
    if(mouse_captured)
    {
        if(action == GLFW_PRESS)
        {
            switch(key)
            {
            case GLFW_KEY_ESCAPE:
                mouse_captured = false;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                cameraptr->reset_input();
                break;

            case GLFW_KEY_W:
                dz = -1;
                break;
            case GLFW_KEY_S:
                dz = 1;
                break;
            case GLFW_KEY_A:
                dx = -1;
                break;
            case GLFW_KEY_D:
                dx = 1;
                break;
            case GLFW_KEY_SPACE:
                dy = 1;
                break;
            case GLFW_KEY_LEFT_SHIFT:
                dy = -1;
                break;
            case GLFW_KEY_F3:
                worldptr->chunkManager->reloadChunkMesh();
                break;
            } 
        }
        else if(action == GLFW_RELEASE)
        {
            switch(key)
            {
            case GLFW_KEY_W:
                dz = 1;
                break;
            case GLFW_KEY_S:
                dz = -1;
                break;
            case GLFW_KEY_A:
                dx = 1;
                break;
            case GLFW_KEY_D:
                dx = -1;
                break;
            case GLFW_KEY_SPACE:
                dy = -1;
                break;
            case GLFW_KEY_LEFT_SHIFT:
                dy = 1;
                break;
            }
        }
    }
    cameraptr->poll_input(glm::vec3(dx, dy, dz));
}

inline void on_cursor_move(GLFWwindow* window, double xpos, double ypos)
{
    if(!mouse_captured)
    {
        return;
    }
    float dx, dy;
    dx = last_x_pos - xpos;
    dy = last_y_pos - ypos;
    playerptr->rotateYaw(-dx * sensitivity);
    playerptr->rotatePitch(-dy * sensitivity);
    last_x_pos = xpos;
    last_y_pos = ypos;
}

#endif
#ifndef APP_CLASS_H
#define APP_CLASS_H

#include <iostream>
#include <exception>

#include "block_type.h"
#include "models.h"
#include "shader.h"
#include "renderer.h"
#include "mesh.h"
#include "geometry.h"
#include "textureManager.h"
#include "player.h"
#include "camera.h"
#include "world.h"
#include "callbacks.h"

class App
{
    ShaderProgram* shaderProgram;
    Player* player;
    PlayerHitray* hitray;
    Camera* camera;
    std::shared_ptr<TextureManager> texture_manager;
    World* world;
    GLFWwindow* window;
    size_t width, height;
    bool vsync;
public:
    App(size_t width, size_t height, bool vsync, bool gl_debug, bool msaa);
    ~App() noexcept;
    void init();
    inline void update(float delta_time);
    inline void draw();
    void run();
};

#endif
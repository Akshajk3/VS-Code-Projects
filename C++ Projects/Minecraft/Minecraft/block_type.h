#ifndef BLOCK_TYPE_CLASS
#define BLOCK_TYPE_CLASS

#include <vector>
#include <memory>

#include "shaderClass.h"
#include "textureManager.h"
#include "Window.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

typedef uint32_t BlockID;

class Block
{
public:
    glm::vec3 Position;
    VAO VAO1;
    Shader shaderProgram = Shader("default.vert", "default.frag");
    TextureManager texture = TextureManager("cobblestone.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    void Init(const Window& window, glm::vec3 position);
    void Destroy();

    void Draw();
};

#endif
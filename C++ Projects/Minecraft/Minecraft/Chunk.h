#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "block_type.h"

class Chunk
{
    const uint32_t CHUNK_WIDTH = 16;
    const uint32_t CHUNK_HEIGHT = 128;
    const uint32_t CHUNK_LENGTH = 16;

    glm::vec2 position;
    BlockID*** blocks;
    

public:
    Chunk(glm::vec2 chunk_position);
    void update_mesh();
};

#endif // !CHUNK_CLASS_H
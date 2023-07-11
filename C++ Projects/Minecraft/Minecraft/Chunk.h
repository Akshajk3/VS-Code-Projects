#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include "World.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Chunk
{
public:
    Chunk(World World, glm::vec3 chunk_position);
};

#endif // !CHUNK_CLASS_H
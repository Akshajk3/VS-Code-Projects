#include "Block.h"

Block::Block(glm::vec3 position)
    : blockPos(position)
{
    Numbers numbers;

    for (int i = 0; i < 6; i++)
    {
        blockVertexPositons.insert(blockVertexPositons.end(), numbers.vertices[i].begin(), numbers.vertices[i].end());
    }
}
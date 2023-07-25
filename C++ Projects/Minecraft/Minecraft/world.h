#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include "textureManager.h"
#include "shader.h"
#include "block_type.h"
#include "chunk_manager.h"
#include "chunk_math.h"

class World
{
    BlockModels models;
    std::shared_ptr<TextureManager> texture_manager;
    std::array<BlockType*, BLOCK_COUNT> block_types;
public:
    std::unique_ptr<ChunkManager> chunkManager;
    World(const std::shared_ptr<TextureManager>& textureManager);
    ~World() noexcept;
    int getBlock(const glm::vec3& pos);
    void setBlock(const glm::vec3& pos, int block);
    void render()
    {
        chunkManager->updateChunkMeshQueue();
        chunkManager->renderChunks();
    }
};

#endif
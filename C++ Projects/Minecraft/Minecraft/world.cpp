#include "world.h"

using BlockTypesPtr = std::array<BlockType*, BLOCK_COUNT>;

World::World(const std::shared_ptr<TextureManager>& textureManager) : texture_manager(textureManager)
{
    std::cout << "Initilizing Texture\n";
    texture_manager->addTexture("textures/cobblestone.png"); // ID: 0
    texture_manager->addTexture("textures/stone.png"); // ID: 1
    texture_manager->addTexture("textures/grass.png"); // ID: 2
    texture_manager->addTexture("textures/grass_side.png"); // ID: 3
    texture_manager->addTexture("textures/dirt.png"); // ID: 4
    texture_manager->addTexture("textures/cobblestone.png"); // ID: 5
    texture_manager->addTexture("textures/planks.png"); // ID: 6

    std::cout << "Initilizing the block models\n";
    block_types[0] = new BlockType("Air", 0, &models.air, {}, true, false);
    block_types[1] = new BlockType("Stone", 1, &models.cube, {1, 1, 1, 1, 1, 1}, false, true);
    //block_types[2] = new BlockType("Grass", 2, &models.cube, {3, 3, 2, 4, 3, 3}, false, true);
    //block_types[3] = new BlockType("Dirt", 3, &models.cube, {4, 4, 4, 4, 4, 4}, false, true);
    //block_types[4] = new BlockType("Cobblestone", 4, &models.cube, {5, 5, 5, 5, 5, 5}, false, true);
    //block_types[5] = new BlockType("Planks", 5, &models.cube, {6, 6, 6, 6, 6, 6}, false, true);
    //chunkManager = std::make_unique<ChunkManager>(&block_types);
    texture_manager->generateMipmaps();
    texture_manager->activate();
}

World::~World()
{
    std::cout << "Freeing Block Models\n";
    for(BlockType* block_type : block_types)
    {
        delete block_type;
    }
}

int World::getBlock(const glm::vec3& pos)
{
    glm::vec2 cpos = to_chunk_pos(pos);
    glm::vec3 lpos = to_local_pos(pos);
    Chunk* chunk = chunkManager->getChunk(cpos);
    if(chunk)
    {
        return chunk->getBlock(lpos);
    }
    return 0;
}

void World::setBlock(const glm::vec3& pos, int block)
{
    glm::vec2 cpos = to_chunk_pos(pos);
    glm::vec3 lpos = to_local_pos(pos);
    Chunk* chunk = chunkManager->getChunk(cpos);
    if(chunk)
    {
        chunk->setBlock(lpos, block);
        chunk->resetIndexCount();
        chunk->update_subchunks_at(lpos);
    }
}
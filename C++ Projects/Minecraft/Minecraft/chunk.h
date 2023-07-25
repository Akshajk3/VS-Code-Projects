#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <vector>
#include <array>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>

#include "renderer.h"
#include "mesh.h"
#include "block_type.h"
#include "batch_info.h"

#include "constants.h"

#include "chunk_math.h"

class Subchunk
{
    Mesh mesh;
    ptrdiff_t offset;
public:
    Subchunk();
    ~Subchunk() noexcept;
    ptrdiff_t getOffset()
    {
        return offset;
    }
    void setOffset(ptrdiff_t newOffset)
    {
        offset = newOffset;
    }
    void pushBlock(const BlockType& block_type, const glm::vec3& pos, const BatchInfo& batchInfo)
    {
        mesh.pushBlock(block_type, pos, batchInfo);
    }
    Mesh& getMesh()
    {
        return mesh;
    }
};

class Chunk
{
    glm::vec2 position;
    std::array<BlockType*, BLOCK_COUNT>* block_types;
    Renderer chunk_renderer;
    BlockID*** blocks;
    std::array<Subchunk, SUBCHUNK_COUNT> subchunks;
    size_t index_count;
public:
    struct _neighbourChunks
    {
        Chunk* east;
        Chunk* west;
        Chunk* south;
        Chunk* north;
    } neighbour_chunks;

    Chunk(const glm::vec2& cpos, std::array<BlockType*, BLOCK_COUNT>* block_types, GLuint* chunk_indices);
    Chunk(const Chunk& other) = delete;
    ~Chunk() noexcept;

    void resetIndexCount()
    {
        index_count = 0;
    }
    const glm::vec2& getPos()
    {
        return position;
    }
    BlockID getBlock(const glm::vec3& pos) const
    {
        uint16_t x = pos.x, y = pos.y, z = pos.z;
        if((x >= 0) && (y >= 0) && (z >= 0))
        {
            if((x < CHUNK_WIDTH) && (y < CHUNK_HEIGHT) && (z < CHUNK_LENGTH))
            {
                return blocks[x][y][z];
            }
        }
        return 0;
    }
    void setBlock(const glm::vec3& pos, BlockID blockid, bool update = false)
    {
        uint16_t x = pos.x, y = pos.y, z = pos.z;
        if((x >= 0) && (y >= 0) && (z >= 0))
        {
            if((x < CHUNK_WIDTH) && (y < CHUNK_HEIGHT) && (z < CHUNK_LENGTH))
            {
                blocks[x][y][z] = blockid;
            }
        }
    }
    bool isOpaqueBlock(BlockID blockid) const
    {
        return !(*block_types)[blockid]->is_transparent;
    }
    bool isOpaqueAt(const glm::vec3& pos) const
    {
        return isOpaqueBlock(getBlock(pos));
    }
private:
    inline bool isOutOfChunk(const glm::vec3& local_pos);
    inline bool canRenderFacing(const glm::vec3& facing_pos);
    bool _canRenderFacingNeigbour(const glm::vec3& facing_pos);
public:
    void generate_mesh(uint8_t sy = 0, uint8_t end = SUBCHUNK_COUNT);
    void update_subchunks_at(const glm::vec3& local_pos);

    void draw()
    {
        chunk_renderer.draw(index_count);
    }
};

#endif
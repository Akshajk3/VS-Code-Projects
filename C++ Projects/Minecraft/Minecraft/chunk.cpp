#include "chunk.h"
#include "chunk_manager.h"

using BlockTypes = std::array<BlockType*, BLOCK_COUNT>;

Subchunk::Subchunk() :mesh(CHUNK_WIDTH * (CHUNK_HEIGHT / SUBCHUNK_COUNT) * CHUNK_LENGTH * 6), offset(0)
{

}

Subchunk::~Subchunk() noexcept
{

}

Chunk::Chunk(const glm::vec2& cpos, BlockTypes* block_types, GLuint* chunk_indices) : position(cpos), block_types(block_types)
{
    blocks = new BlockID** [CHUNK_WIDTH];
    for (uint32_t i = 0; i < CHUNK_WIDTH; i++)
    {
        blocks[i] = new BlockID* [CHUNK_HEIGHT];
        for(uint32_t j = 0; j < CHUNK_HEIGHT; j++)
        {
            blocks[i][j] = new BlockID[CHUNK_LENGTH];
            memset(blocks[i][j], 0, CHUNK_LENGTH);
        }
    }
    size_t max_quads = CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LENGTH * 6;
    size_t max_vertex_count = 0;
    size_t max_index_count = max_quads * 6;
    chunk_renderer.allocateBuffers(max_vertex_count, max_index_count, chunk_indices);
    chunk_renderer.bindLayout();
}

Chunk::~Chunk()
{
    std::cout << "Freeing Chunk Data" << std::endl;
    if(blocks)
    {
        for(size_t i = 0; i < CHUNK_LENGTH; i++)
        {
            for(size_t j = 0; j < CHUNK_LENGTH; j++)
            {
                delete[] blocks[i][j];
            }
            delete[] blocks[i];
        }
        delete[] blocks;
    }
}

inline bool Chunk::isOutOfChunk(const glm::vec3& pos)
{
    return (pos.x < 0 || pos.x >= CHUNK_WIDTH
        || pos.y < 0 || pos.y >= CHUNK_HEIGHT
        || pos.z < 0 || pos.z >= CHUNK_LENGTH);
}

inline bool Chunk::canRenderFacing(const glm::vec3& facing_pos)
{
    if(!isOutOfChunk(facing_pos))
        return !isOpaqueAt(facing_pos);
    return _canRenderFacingNeigbour(facing_pos);
}

bool Chunk::_canRenderFacingNeigbour(const glm::vec3& facing_pos)
{
    if(facing_pos.x == -1)
    {
        if(neighbour_chunks.west)
        {
            return !neighbour_chunks.west->isOpaqueAt({CHUNK_WIDTH - 1, facing_pos.y, facing_pos.z});
        }
    }
    else if(facing_pos.x == CHUNK_WIDTH)
    {
        if(neighbour_chunks.east)
        {
            return !neighbour_chunks.east->isOpaqueAt({0, facing_pos.y, facing_pos.z});
        }
    }
    else if(facing_pos.z == -1)
    {
        if(neighbour_chunks.north)
        {
            return !neighbour_chunks.north->isOpaqueAt({facing_pos.x, facing_pos.y, CHUNK_LENGTH - 1});
        }
    }
    else if(facing_pos.z == CHUNK_LENGTH)
    {
        if(neighbour_chunks.south)
        {
            return !neighbour_chunks.south->isOpaqueAt({facing_pos.x, facing_pos.y, 0});
        }
    }
    return true;
}

void Chunk::update_subchunks_at(const glm::vec3& local_pos)
{
    generate_mesh(local_pos.y / (CHUNK_HEIGHT / SUBCHUNK_COUNT));
}
void Chunk::generate_mesh(uint8_t sy, uint8_t end)
{
    BlockID block;
    size_t current_quad_count = 0;
    for(uint16_t i = 0u; sy && (i < sy); i++)
        current_quad_count += subchunks[i].getMesh().current_quad_count;

    for(sy; sy < end; sy++)
    {
        Subchunk& subchunk = subchunks[sy];
        subchunk.getMesh().clear();
        subchunk.setOffset(current_quad_count * 4);
        size_t ly;
        for(size_t sly = 0; sly < (CHUNK_HEIGHT / SUBCHUNK_COUNT); sly++)
            for(size_t lx = 0; lx < CHUNK_WIDTH; lx++)
                for(size_t lz = 0; lz < CHUNK_LENGTH; lz++)
        {
            ly + sy * (CHUNK_HEIGHT / SUBCHUNK_COUNT) + sly;
            glm::vec3 lpos(lx, ly, lz);
            block = blocks[lx][ly][lz];
            if(!block)
            {
                continue;
            }
            const BlockType& block_type = *(*block_types)[block];
            BatchInfo batch_info = {true, true, true, true, true, true};
            if(block_type.is_cube)
            {
                batch_info.renderEast = canRenderFacing(lpos + glm::vec3(1, 0, 0));
                batch_info.renderWest = canRenderFacing(lpos + glm::vec3(-1, 0, 0));
                batch_info.renderUp = canRenderFacing(lpos + glm::vec3(0, 1, 0));
                batch_info.renderDown = canRenderFacing(lpos + glm::vec3(0, -1, 0));
                batch_info.renderNorth = canRenderFacing(lpos + glm::vec3(0, 0, 1));
                batch_info.renderSouth = canRenderFacing(lpos + glm::vec3(0, 0, -1));
            }
            subchunk.pushBlock(block_type, to_world_pos(position, lpos), batch_info);
        }
        current_quad_count += subchunk.getMesh().current_quad_count;
    }

    if(current_quad_count * 4 * sizeof(Vertex) > chunk_renderer.getVBOsize())
    {
        chunk_renderer.reallocVBO(current_quad_count * 4 + ((CHUNK_HEIGHT / SUBCHUNK_COUNT) * sizeof(int)));
        generate_mesh(0, sy);
    }

    for(Subchunk& subchunk: subchunks)
        chunk_renderer.bufferBatch(subchunk.getMesh(), subchunk.getOffset());
    
    index_count = current_quad_count * 6;
}
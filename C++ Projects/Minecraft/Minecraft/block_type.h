#ifndef BLOCK_TYPE_CLASS_H
#define BLOCK_TYPE_CLASS_H

#include <vector>
#include <memory>

#include "geometry.h"
#include "models.h"
#include "textureManager.h"

typedef uint32_t BlockID;

class BlockType
{
    Model* model;
    Quad* quads;
    std::shared_ptr<TextureManager> texture_manager;
public:
    bool is_transparent;
    bool is_cube;
    const char* name;
    uint32_t id;
    BlockType(const char* name, size_t block_id, Model* model, const std::vector<size_t>& texture_layout, bool is_transparent, bool is_cube);
    BlockType(const BlockType& other);
    ~BlockType() noexcept;
    const Quad* get_quads() const
    {
        return quads;
    }
    size_t get_quad_number() const
    {
        return model->get_quad_number();
    }
};

#endif
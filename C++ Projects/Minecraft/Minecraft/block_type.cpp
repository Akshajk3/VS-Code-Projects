#include "block_type.h"

BlockType::BlockType(const char* name, size_t block_id, Model* model, const std::vector<size_t>& texture_layout, bool is_transparent, bool is_cube)
    : name(name), id(block_id), texture_manager(texture_manager), model(model), is_transparent(is_transparent), is_cube(is_cube)
{
    if(model->get_quad_number())
    {
        quads = new Quad[model->get_quad_number()];
        memcpy(quads, model->get_quads(), model->get_quad_number() * sizeof(Quad));
        
        for(uint8_t i = 0; i < model->get_quad_number(); i++)
        {
            for(Vertex& vertex : quads[i].vertices)
            {
                vertex.tex_index = texture_layout[i];
            }
        }
    }
    else
    {
        quads = nullptr;
    }
}

BlockType::BlockType(const BlockType& other) : name(other.name), id(other.id), texture_manager(other.texture_manager), model(other.model)
{
    quads = new Quad[other.get_quad_number()];
    memcpy(quads, other.get_quads(), other.get_quad_number() * sizeof(Quad));
}

BlockType::~BlockType() noexcept
{
    delete[] quads;
}
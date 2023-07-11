#ifndef GEOMETRY_CLASS_H
#define GEOMETRY_CLASS_H

#include <array>
#include <iostream>

namespace Geometry
{
    struct Vertex
    {
        float position[3];
        uint32_t tex_UV;
        uint32_t tex_index;
        float shading_value;
    };

    struct Quad
    {
        Vertex vertices[4];
    };

    const std::array<uint32_t, 6> quad_indices
    {
        0, 1, 2,
        0, 2, 3
    };
    
}
#endif
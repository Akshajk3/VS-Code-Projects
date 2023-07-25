#ifndef MODELS
#define MODELS

#include <memory>

#include "geometry.h"

static Quad cube_vertex_data[6] = {
    /* Vertex Positions */  /* Tex Coords  */		/* Shading */
    {{
        { { 0.5,  0.5,  0.5 },      { 0u },  { 0u }, 		{ 0.8 } },
        { { 0.5, -0.5,  0.5 },		{ 1u },  { 0u },		{ 0.8 } },
        { { 0.5, -0.5, -0.5 },		{ 2u },  { 0u },		{ 0.8 } },
        { { 0.5,  0.5, -0.5 },		{ 3u },  { 0u },		{ 0.8 } }
    }},
    {{
        { {-0.5,  0.5, -0.5 },		{ 0u },  { 0u },		{ 0.8 } },
        { {-0.5, -0.5, -0.5 },		{ 1u },  { 0u },		{ 0.8 } },
        { {-0.5, -0.5,  0.5 },		{ 2u },  { 0u },		{ 0.8 } },
        { {-0.5,  0.5,  0.5 },		{ 3u },  { 0u },		{ 0.8 } },
    }},
    {{
        { { 0.5,  0.5,  0.5 },		{ 0u },  { 0u },		{ 1.0 } },
        { { 0.5,  0.5, -0.5 },		{ 1u },  { 0u },		{ 1.0 } },
        { {-0.5,  0.5, -0.5 },		{ 2u },  { 0u },		{ 1.0 } },
        { {-0.5,  0.5,  0.5 },		{ 3u },  { 0u },		{ 1.0 } },
    }},
    {{
        { {-0.5, -0.5,  0.5 },		{ 0u },  { 0u },		{ 0.4 } },
        { {-0.5, -0.5, -0.5 },		{ 1u },  { 0u },		{ 0.4 } },
        { { 0.5, -0.5, -0.5 },		{ 2u },  { 0u },		{ 0.4 } },
        { { 0.5, -0.5,  0.5 },		{ 3u },  { 0u },		{ 0.4 } },
    }},
    {{
        { { -0.5,  0.5,  0.5 },		{ 0u },  { 0u },		{ 0.6 } },
        { { -0.5, -0.5,  0.5 },		{ 1u },  { 0u },		{ 0.6 } },
        { { 0.5, -0.5,  0.5 },		{ 2u },  { 0u },		{ 0.6 } },
        { { 0.5,  0.5,  0.5 },		{ 3u },  { 0u },		{ 0.6 } },
    }},
    {{
        { { 0.5,  0.5, -0.5 },		{ 0u },  { 0u },		{ 0.6 } },
        { { 0.5, -0.5, -0.5 },		{ 1u },  { 0u },		{ 0.6 } },
        { {-0.5, -0.5, -0.5 },		{ 2u },  { 0u },		{ 0.6 } },
        { {-0.5,  0.5, -0.5 },		{ 3u },  { 0u },		{ 0.6 } },
    }}
};

class Model
{
protected:
    Quad* quads;
public:
    virtual const Quad* get_quads() const = 0;
    virtual uint16_t get_quad_number() const = 0;
};

class Air : public Model
{
public:
    const Quad* get_quads() const override
    {
        return nullptr;
    }
    uint16_t get_quad_number() const override
    {
        return 0;
    }
};

class Cube : public Model
{
    Quad* quads;
public:
    Cube() : quads(cube_vertex_data)
    {

    }
    const Quad* get_quads() const override
    {
        return quads;
    }
    uint16_t get_quad_number() const override
    {
        return 6;
    }
};

struct BlockModels
{
    Cube cube;
    Air air;
};

#endif
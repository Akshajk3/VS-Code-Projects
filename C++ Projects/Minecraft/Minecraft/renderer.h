#ifndef RENDERER_CLASS_H
#define RENDERER_CLASS_H

#include "shader.h"
#include "buffers.h"
#include "vertex_array.h"

#include "mesh.h"

class Renderer
{
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ibo;
    ShaderProgram* shaderProgram;
public:
    Renderer() : vao(), vbo(), ibo(), shaderProgram()
    {

    }
    ~Renderer() noexcept
    {

    }
    size_t getVBOsize()
    {
        return vbo.current_size;
    }

    void allocateBuffers(size_t max_vertex_count, size_t max_index_count, GLuint* indices)
    {
        vao.bind();
        vbo.allocate(max_vertex_count * sizeof(Vertex));
        ibo.bufferData(indices,  max_index_count * sizeof(GLuint));
    }
    void reallocVBO(size_t new_capacity)
    {
        vbo.allocate(new_capacity * sizeof(Vertex));
    }

    void bufferBatch(const Mesh& mesh,  ptrdiff_t offset)
    {
        vao.bind();
        vbo.bufferSubData(mesh.getVertexData().data(), mesh.getVertexData().size(), offset * sizeof(Vertex));
    }

    void bindLayout()
    {
        vao.linkAttrib(&vbo, 0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, position));
        vao.linkAttrib(&vbo, 1, 3, GL_UNSIGNED_INT, sizeof(Vertex), offsetof(Vertex, tex_UV));
        vao.linkAttrib(&vbo, 2, 2, GL_UNSIGNED_INT, sizeof(Vertex), offsetof(Vertex, tex_index));
        vao.linkAttrib(&vbo, 3, 1, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, shading_value));
    }

    void bindAll() const
    {
        vao.bind();
        vbo.bind();
        ibo.bind();
    }

    void draw(size_t index_count) const
    {
        vao.bind();
        ibo.bind();
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, nullptr);
    }
};

#endif
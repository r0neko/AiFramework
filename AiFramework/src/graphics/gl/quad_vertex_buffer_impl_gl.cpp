#include <glad/glad.h>
#include <graphics/quad_vertex_buffer.hpp>

using namespace ai_framework::graphics;

void QuadVertexBuffer::create() {
    if (created())
        return;

    VertexBuffer::create();

    if (!VertexBuffer::created())
        return;

    if (ebo == -1)
        glGenBuffers(1, &ebo);

    if (ebo == -1)
        return;
}

void QuadVertexBuffer::bind() {
    VertexBuffer::bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void QuadVertexBuffer::resize() {
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    VertexBuffer::resize();
}

void QuadVertexBuffer::draw() {
    // minimum 2 triangles are required
    if (indices.size() / 3 < 2)
        return;

    bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
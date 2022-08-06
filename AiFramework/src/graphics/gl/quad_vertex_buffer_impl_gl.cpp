#include <glad/glad.h>
#include <graphics/quad_vertex_buffer.hpp>

using namespace ai_framework::graphics;

template <typename T>
void QuadVertexBuffer<T>::create() {
    if (created())
        return;

    VertexBuffer<T>::create();

    if (!VertexBuffer<T>::created())
        return;

    if (ebo == -1)
        glGenBuffers(1, &ebo);

    if (ebo == -1)
        return;
}

template <typename T>
void QuadVertexBuffer<T>::bind() {
    if (!created())
        create();

    VertexBuffer<T>::bind();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}

template <typename T>
void QuadVertexBuffer<T>::resize() {
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    VertexBuffer<T>::resize();
}

template <typename T>
void QuadVertexBuffer<T>::draw() {
    // minimum 2 triangles are required
    if (indices.size() / 3 < 2)
        return;

    VertexBuffer<T>::vertices[0].use_shader();
    bind();
    glDrawElements(GL_TRIANGLES, (GLsizei) indices.size(), GL_UNSIGNED_INT, 0);
}

// do template initialization to prevent linking errors
template struct QuadVertexBuffer<Vertex2D>;
template struct QuadVertexBuffer<ColorVertex2D>;
template struct QuadVertexBuffer<TexturedVertex2D>;
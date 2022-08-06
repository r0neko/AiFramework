#include <glad/glad.h>
#include <graphics/vertex_buffer.hpp>

using namespace ai_framework::graphics;

template <typename T>
void VertexBuffer<T>::create() {
    if (created())
        return;

    is_created = false;

    if (vbo == -1)
        glGenBuffers(1, &vbo);

    if (vao == -1)
        glGenVertexArrays(1, &vao);

    if (vbo == -1 || vao == -1)
        return;

    is_created = true;
}

template <typename T>
void VertexBuffer<T>::destroy() {
    if (vbo >= 0) {
        glDeleteBuffers(1, &vbo);
        vbo = -1;
    }

    if (vao >= 0) {
        glDeleteVertexArrays(1, &vao);
        vao = -1;
    }

    is_created = false;
}

template <typename T>
void VertexBuffer<T>::bind() {
    if (!created())
        create();

    glBindVertexArray(vao);
}

template <typename T>
void VertexBuffer<T>::resize() {
    if (vertices.size() == 0)
        return;

    bind();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(T) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    vertices[0].set_attributes();
}

template <typename T>
void VertexBuffer<T>::draw() {
    vertices[0].use_shader();
    bind();
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei) vertices.size());
}

// do template initialization to prevent linking errors
template struct VertexBuffer<Vertex2D>;
template struct VertexBuffer<ColorVertex2D>;
template struct VertexBuffer<TexturedVertex2D>;
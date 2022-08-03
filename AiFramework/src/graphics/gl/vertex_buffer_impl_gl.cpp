#include <glad/glad.h>
#include <graphics/vertex_buffer.hpp>

using namespace ai_framework::graphics;

void VertexBuffer::create() {
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

void VertexBuffer::destroy() {
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

void VertexBuffer::bind() {
    glBindVertexArray(vao);
}

void VertexBuffer::resize() {
    bind();

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_INT, GL_FALSE, sizeof(Vertex2D), (void *) sizeof(FloatVector2));
    glEnableVertexAttribArray(1);
}

void VertexBuffer::draw() {
    bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
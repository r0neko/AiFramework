#include <graphics/graphics_api.hpp>
#include <graphics/vertex_buffer.hpp>

using namespace ai_framework::graphics;

template <typename T>
void VertexBuffer<T>::create() {
    if (created())
        return;

    is_created = false;

    if (vbo == AI_FRAMEWORK_NULL)
        vbo = api->create_buffer();

    if (vao == AI_FRAMEWORK_NULL)
        vao = api->create_vertex_array();

    if (vbo == AI_FRAMEWORK_NULL || vao == AI_FRAMEWORK_NULL)
        return;

    is_created = true;
}

template <typename T>
void VertexBuffer<T>::destroy() {
    if (vbo != AI_FRAMEWORK_NULL) {
        api->delete_buffer(vbo);
        vbo = AI_FRAMEWORK_NULL;
    }

    if (vao != AI_FRAMEWORK_NULL) {
        api->delete_vertex_array(vao);
        vao = AI_FRAMEWORK_NULL;
    }

    is_created = false;
}

template <typename T>
void VertexBuffer<T>::bind() {
    if (!created())
        create();

    api->bind_vertex_array(vao);
}

template <typename T>
void VertexBuffer<T>::resize() {
    if (vertices.size() == 0)
        return;

    bind();

    api->bind_buffer(vbo, BufferType::ARRAY_BUFFER);
    api->set_buffer_data(BufferType::ARRAY_BUFFER, sizeof(T) * vertices.size(), &vertices[0], UsageMode::DYNAMIC_DRAW);

    vertices[0].set_attributes();
}

template <typename T>
void VertexBuffer<T>::draw() {
    vertices[0].use_shader();

    bind();

    api->draw_buffer(DrawMode::TRIANGLES, 0, (int) vertices.size());
}

// do template initialization to prevent linking errors
template struct graphics::VertexBuffer<Vertex2D>;
template struct graphics::VertexBuffer<ColorVertex2D>;
template struct graphics::VertexBuffer<TexturedVertex2D>;
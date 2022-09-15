#include <graphics/graphics_api.hpp>
#include <graphics/quad_vertex_buffer.hpp>

using namespace ai_framework::graphics;

template <typename T>
void QuadVertexBuffer<T>::create() {
    if (created())
        return;

    VertexBuffer<T>::create();

    if (!VertexBuffer<T>::created())
        return;

    if (ebo == AI_FRAMEWORK_NULL)
        ebo = api->create_buffer();

    if (ebo == AI_FRAMEWORK_NULL)
        return;
}

template <typename T>
void QuadVertexBuffer<T>::bind() {
    if (!created())
        create();

    VertexBuffer<T>::bind();
    api->bind_buffer(ebo, BufferType::ELEMENT_ARRAY_BUFFER);
}

template <typename T>
void QuadVertexBuffer<T>::resize() {
    bind();
    VertexBuffer<T>::resize();

    api->set_buffer_data(BufferType::ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], UsageMode::DYNAMIC_DRAW);
}

template <typename T>
void QuadVertexBuffer<T>::draw() {
    // minimum 2 triangles are required
    if (indices.size() / 3 < 2)
        return;

    VertexBuffer<T>::vertices[0].use_shader();
    bind();
    api->draw_elements(DrawMode::TRIANGLES, 0, indices.size(), DataType::UNSIGNED_INT);
}

// do template initialization to prevent linking errors
template struct graphics::QuadVertexBuffer<Vertex2D>;
template struct graphics::QuadVertexBuffer<ColorVertex2D>;
template struct graphics::QuadVertexBuffer<TexturedVertex2D>;
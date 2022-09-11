#ifndef QUAD_VERTEX_BUFFER_HPP
#define QUAD_VERTEX_BUFFER_HPP

#include <framework_build.hpp>

#include <graphics/vertex_buffer.hpp>

#include <vector>

namespace ai_framework::graphics {
    template <typename T>
    struct AI_API QuadVertexBuffer : VertexBuffer<T> {
        void clear() {
            VertexBuffer<T>::clear();
            resize();
        }

        void add_vertex(const T &vertex) {
            VertexBuffer<T>::add_vertex(vertex);
            resize();
        }

        bool created() const {
            return ebo != nullptr && VertexBuffer<T>::created();
        }

        void create();

        void resize();
        void bind();
        void draw();

        bool can_render() {
            return created() && VertexBuffer<T>::can_render();
        }

      private:
        opaque_t ebo{nullptr};

        // to do: make it dynamic
        std::vector<unsigned int> indices = {
            0,
            1,
            3,
            1,
            2,
            3};
    };
} // namespace ai_framework::graphics

#endif
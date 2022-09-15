#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <framework_build.hpp>
#include <graphics/vertex.hpp>

#include <vector>

#include <cstdint>

namespace ai_framework::graphics {
    template <typename T>
    struct AI_API VertexBuffer {
        void clear() {
            vertices.clear();
            resize();
        }

        void add_vertex(const T &vertex) {
            vertices.push_back(vertex);
            resize();
        }

        bool created() const {
            return vbo != AI_FRAMEWORK_NULL && vao != AI_FRAMEWORK_NULL && is_created;
        }

        bool can_render() {
            return created() && vertices.size() >= 1 && vertices[0].can_render();
        }

        void create();
        void destroy();

        void resize();
        void bind();
        void draw();

      protected:
        std::uintptr_t vbo{AI_FRAMEWORK_NULL};
        std::uintptr_t vao{AI_FRAMEWORK_NULL};

        bool is_created = false;
        std::vector<T> vertices;
    };
} // namespace ai_framework::graphics

#endif
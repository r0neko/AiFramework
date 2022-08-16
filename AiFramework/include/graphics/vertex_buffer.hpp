#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <framework_build.hpp>
#include <graphics/vertex.hpp>

#include <vector>

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
            return vbo != nullptr && vao != nullptr && is_created;
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
        opaque_t vbo{nullptr};
        opaque_t vao{nullptr};

        bool is_created = false;
        std::vector<T> vertices;
    };
} // namespace ai_framework::graphics

#endif
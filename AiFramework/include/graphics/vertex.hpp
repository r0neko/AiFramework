#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <framework_build.hpp>

#include "color.hpp"
#include <generic/vector2.hpp>

#include <vector>

namespace ai_framework::graphics {
#pragma pack(push, 1)
    struct Vertex2D {
        float x, y;
        Color color;
    };
#pragma pack(pop)

    struct AI_API VertexBuffer {
        void add_2d_vertex(const Vertex2D &vertex) {
            vertices.push_back(vertex);
        }

        bool created() const {
            return vbo != -1 && vao != -1 && is_created;
        }

        void create();
        void destroy();

        void resize();
        void bind(bool bind_only = false);
        void draw();

      private:
        unsigned int vbo = -1;
        unsigned int vao = -1;

        bool is_created = false;
        std::vector<Vertex2D> vertices;
    };
} // namespace ai_framework::graphics

#endif
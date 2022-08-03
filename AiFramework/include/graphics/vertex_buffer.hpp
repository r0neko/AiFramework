#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include <framework_build.hpp>

#include <graphics/vertex.hpp>

#include <vector>

namespace ai_framework::graphics {
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
        void bind();
        void draw();

      protected:
        unsigned int vbo = -1;
        unsigned int vao = -1;

        bool is_created = false;

      private:
        std::vector<Vertex2D> vertices;
    };
} // namespace ai_framework::graphics

#endif
#ifndef QUAD_VERTEX_BUFFER_HPP
#define QUAD_VERTEX_BUFFER_HPP

#include <framework_build.hpp>

#include <graphics/vertex_buffer.hpp>

#include <vector>

namespace ai_framework::graphics {
    struct AI_API QuadVertexBuffer : VertexBuffer {
        bool created() const {
            return ebo != -1 && VertexBuffer::created();
        }

        void create();

        void resize();
        void bind();
        void draw();

      private:
        unsigned int ebo = -1;
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
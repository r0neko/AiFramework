#ifndef SHADER_INTERNAL_HPP
#define SHADER_INTERNAL_HPP

#include <graphics/shader_program.hpp>

using namespace ai_framework::graphics;

namespace ai_framework::shaders {
    inline ShaderProgram vertex_2d_shader("Vertex2D");
    inline ShaderProgram color_vertex_2d_shader("ColorVertex2D");
    inline ShaderProgram textured_vertex_2d_shader("TexturedVertex2D");
} // namespace ai_framework::shaders

#endif
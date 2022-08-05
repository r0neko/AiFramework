#include <framework/shaders_internal.hpp>
#include <graphics/vertex.hpp>

using namespace ai_framework::graphics;

bool Vertex2D::can_render() {
    return shaders::vertex_2d_shader.compiled();
}

void Vertex2D::use_shader() {
    shaders::vertex_2d_shader.use();
}

bool ColorVertex2D::can_render() {
    return shaders::color_vertex_2d_shader.compiled();
}

void ColorVertex2D::use_shader() {
    shaders::color_vertex_2d_shader.use();
}
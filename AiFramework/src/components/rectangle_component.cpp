#include <components/rectangle_component.hpp>
#include <framework/shaders_internal.hpp>
#include <graphics/quad_vertex_buffer.hpp>
#include <graphics/vertex.hpp>

using namespace ai_framework::components;
using namespace ai_framework::graphics;
using namespace ai_framework::shaders;

QuadVertexBuffer<ColorVertex2D> quad_buffer;

bool r_comp_first_frame = true;

void RectangleComponent::draw() {
    if (!r_comp_first_frame && !quad_buffer.can_render())
        return;

    quad_buffer.clear();

    quad_buffer.add_vertex({0.5f, 0.5f, colors::red});    // top right
    quad_buffer.add_vertex({0.5f, -0.5f, colors::green}); // bottom right
    quad_buffer.add_vertex({-0.5f, -0.5f, colors::blue}); // bottom left
    quad_buffer.add_vertex({-0.5f, 0.5f, colors::white}); // top left

    quad_buffer.draw();

    r_comp_first_frame = false;
}
#include <components/rectangle_component.hpp>
#include <framework/shaders_internal.hpp>
#include <graphics/texture.hpp>

using namespace ai_framework::components;
using namespace ai_framework::graphics;
using namespace ai_framework::shaders;

//Texture test_tex{{"./assets/dank.png"}};

void RectangleComponent::draw(BaseApp *app) {
    if (!r_comp_first_frame && !quad_buffer.can_render())
        return;

    quad_buffer.clear();

    // textured vertex rendering
    // quad_buffer.add_vertex({0.5f, 0.5f, colors::red, 1.0f, 1.0f});    // top right
    // quad_buffer.add_vertex({0.5f, -0.5f, colors::green, 1.0f, 0.0f}); // bottom right
    // quad_buffer.add_vertex({-0.5f, -0.5f, colors::blue, 0.0f, 0.0f}); // bottom left
    // quad_buffer.add_vertex({-0.5f, 0.5f, colors::white, 0.0f, 1.0f}); // top left

    quad_buffer.add_vertex({position.x + size.x, position.y, color});          // top right
    quad_buffer.add_vertex({position.x + size.x, position.y + size.y, color}); // bottom right
    quad_buffer.add_vertex({position.x, position.y + size.y, color});          // bottom left
    quad_buffer.add_vertex({position, color});                                 // top left

    // test_tex.use();
    quad_buffer.draw();

    r_comp_first_frame = false;
}
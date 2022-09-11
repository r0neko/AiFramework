#include <framework/shaders_internal.hpp>
#include <graphics/graphics_api.hpp>
#include <graphics/vertex.hpp>

using namespace ai_framework;
using namespace ai_framework::graphics;

int _max_enabled_attr = 0;

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

bool TexturedVertex2D::can_render() {
    return shaders::textured_vertex_2d_shader.compiled();
}

void TexturedVertex2D::use_shader() {
    shaders::textured_vertex_2d_shader.use();
}

void graphics::enable_attributes(int amount) {
    if (_max_enabled_attr == amount)
        return;

    for (int i = 0; i < amount; i++) {
        if (i < amount)
            api->enable_vertex_attribute(i);
        else
            api->disable_vertex_attribute(i);
    }

    _max_enabled_attr = amount;
}

void Vertex2D::set_attributes() {
    /*
     * Each vertex has the following structure in memory:
     * +-------+
     * | X | Y |
     * +-------+
     * | 0 | 1 |
     * +-------+
     * Therefore, there are 2 floats(X and Y) that serve the purpose of setting
     * the position.
     */

    api->define_vertex_attribute(0, 2, DataType::FLOAT, sizeof(Vertex2D));

    enable_attributes(1);
}

void ColorVertex2D::set_attributes() {
    /*
     * Each vertex has the following structure in memory:
     * +-----------------------+
     * | X | Y | R | G | B | A |
     * +-----------------------+
     * | 0 | 1 | 2 | 3 | 4 | 5 |
     * +-----------------------+
     * Therefore, there are 2 floats(X and Y) that serve the purpose of setting
     * the position and 4 bytes(R, G, B, A) which serve as the color.
     */

    api->define_vertex_attribute(0, 2, DataType::FLOAT, sizeof(ColorVertex2D));
    api->define_vertex_attribute(1, 3, DataType::UNSIGNED_BYTE, sizeof(ColorVertex2D), sizeof(FloatVector2));

    enable_attributes(2);
}

void TexturedVertex2D::set_attributes() {
    /*
     * Each vertex has the following structure in memory:
     * +-------------------------------+
     * | X | Y | R | G | B | A | X | Y |
     * +-------------------------------+
     * | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
     * +-------------------------------+
     * Therefore, there are 2 floats(X and Y) that serve the purpose of setting
     * the position, 4 bytes(R, G, B, A) which serve as the color,
     * and 2 more floats(X and Y) which serve the purpose of translating the texture sample.
     */

    api->define_vertex_attribute(0, 2, DataType::FLOAT, sizeof(TexturedVertex2D));
    api->define_vertex_attribute(1, 4, DataType::UNSIGNED_BYTE, sizeof(TexturedVertex2D), sizeof(FloatVector2));
    api->define_vertex_attribute(2, 2, DataType::FLOAT, sizeof(TexturedVertex2D), sizeof(FloatVector2) + sizeof(Color));

    enable_attributes(3);
}
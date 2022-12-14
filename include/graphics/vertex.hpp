#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <framework_build.hpp>

#include <generic/vector2.hpp>
#include <graphics/color.hpp>

namespace ai_framework::graphics {
    void enable_attributes(int amount);

#pragma pack(push, 1)
    struct Vertex2D {
        Vertex2D(float x, float y)
            : x(x), y(y) {
        }

        Vertex2D(const FloatVector2 &vector)
            : x(vector.x), y(vector.y) {
        }

        void set_attributes();
        void use_shader();
        bool can_render();

        float x, y;
    };

    struct ColorVertex2D : Vertex2D {
        ColorVertex2D(float x, float y, const Color &color)
            : Vertex2D(x, y), color(color) {
        }

        ColorVertex2D(const FloatVector2 &vector, const Color &color)
            : Vertex2D(vector), color(color) {
        }

        void set_attributes();
        void use_shader();
        bool can_render();

        Color color;
    };

    struct TexturedVertex2D : ColorVertex2D {
        TexturedVertex2D(float x, float y, const Color &color, float sx, float sy)
            : ColorVertex2D(x, y, color), sx(sx), sy(sy) {
        }

        TexturedVertex2D(const FloatVector2 &vector, const Color &color, const FloatVector2 &sample)
            : ColorVertex2D(vector, color), sx(sample.x), sy(sample.y) {
        }

        void set_attributes();
        void use_shader();
        bool can_render();

        float sx, sy;
    };
#pragma pack(pop)
} // namespace ai_framework::graphics

#endif
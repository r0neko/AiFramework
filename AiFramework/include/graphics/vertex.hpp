#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <framework_build.hpp>

#include <graphics/color.hpp>
#include <generic/vector2.hpp>

namespace ai_framework::graphics {
#pragma pack(push, 1)
    struct Vertex2D {
        Vertex2D(float x, float y, const Color &color)
            : x(x), y(y), color(color) {
        }

        Vertex2D(const FloatVector2 &vector, const Color &color)
            : x(vector.x), y(vector.y), color(color) {
        }

        float x, y;
        Color color;
    };
#pragma pack(pop)
} // namespace ai_framework::graphics

#endif
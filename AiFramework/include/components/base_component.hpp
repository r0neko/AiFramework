#ifndef BASE_COMPONENT_HPP
#define BASE_COMPONENT_HPP

#include <framework_build.hpp>
#include <generic/vector2.hpp>
#include <graphics/color.hpp>

using namespace ai_framework;
using namespace ai_framework::graphics;

namespace ai_framework::components {
    struct AI_API BaseComponent {
        BaseComponent(const FloatVector2 &pos, const FloatVector2 &sz, const Color &col)
            : position(pos), size(sz), color(col) {
        }

        BaseComponent(const FloatVector2 &pos, const FloatVector2 &sz)
            : position(pos), size(sz), color(colors::white) {
        }

        virtual void draw() = 0;

        FloatVector2 position;
        FloatVector2 size;
        Color color;
    };
} // namespace ai_framework::components

#endif
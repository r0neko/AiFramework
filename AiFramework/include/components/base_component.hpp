#ifndef BASE_COMPONENT_HPP
#define BASE_COMPONENT_HPP

#include <framework/base_app.hpp>
#include <framework_build.hpp>
#include <generic/vector2.hpp>
#include <graphics/color.hpp>

using namespace ai_framework;
using namespace ai_framework::framework;
using namespace ai_framework::graphics;

namespace ai_framework::components {
    struct AI_API BaseComponent {
        BaseComponent(const FloatVector2 &pos, const FloatVector2 &sz)
            : position(pos), size(sz) {
        }

        virtual void draw(BaseApp *app) = 0;

        FloatVector2 position;
        FloatVector2 size;
    };
} // namespace ai_framework::components

#endif
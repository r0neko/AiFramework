#ifndef RECTANGLE_COMPONENT_HPP
#define RECTANGLE_COMPONENT_HPP

#include <components/base_component.hpp>
#include <framework_build.hpp>

namespace ai_framework::components {
    /// <summary>
    /// DEVELOPMENT TEST COMPONENT: Draws a rectangle. For now, no coords are used.
    /// </summary>
    struct AI_API RectangleComponent : BaseComponent {
        RectangleComponent(const FloatVector2 &pos, const FloatVector2 &sz, const Color &col)
            : BaseComponent(pos, sz, col) {
        }

        RectangleComponent(const FloatVector2 &pos, const FloatVector2 &sz)
            : BaseComponent(pos, sz) {
        }

        void draw(BaseApp *app) override;
    };
} // namespace ai_framework::components

#endif
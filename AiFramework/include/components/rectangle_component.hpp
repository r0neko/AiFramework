#ifndef RECTANGLE_COMPONENT_HPP
#define RECTANGLE_COMPONENT_HPP

#include <components/base_component.hpp>
#include <framework_build.hpp>

namespace ai_framework::components {
    /// <summary>
    /// DEVELOPMENT TEST COMPONENT: Draws a rectangle. For now, no coords are used.
    /// </summary>
    struct AI_API RectangleComponent : BaseComponent {
        void draw() override;
    };
} // namespace ai_framework::components

#endif
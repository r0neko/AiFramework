#ifndef RECTANGLE_COMPONENT_HPP
#define RECTANGLE_COMPONENT_HPP

#include <framework_build.hpp>

#include <components/base_component.hpp>
#include <graphics/quad_vertex_buffer.hpp>
#include <graphics/vertex.hpp>

namespace ai_framework::components {
    /// <summary>
    /// DEVELOPMENT TEST COMPONENT: Draws a rectangle. For now, no coords are used.
    /// </summary>
    struct AI_API RectangleComponent : BaseComponent {
        RectangleComponent(const FloatVector2 &pos, const FloatVector2 &sz, const Color &col)
            : BaseComponent(pos, sz), color(col) {
        }

        RectangleComponent(const FloatVector2 &pos, const FloatVector2 &sz)
            : BaseComponent(pos, sz), color(colors::white) {
        }

        void draw(BaseApp *app) override;

        Color color;

      private:
        QuadVertexBuffer<ColorVertex2D> quad_buffer;
        bool r_comp_first_frame = true;
    };
} // namespace ai_framework::components

#endif
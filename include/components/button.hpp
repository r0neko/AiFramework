#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <components/base_component.hpp>
#include <generic/signal_source.hpp>
#include <graphics/color.hpp>
#include <graphics/quad_vertex_buffer.hpp>
#include <graphics/vertex.hpp>

namespace ai_framework::components {
    /// <summary>
    /// A clickable component that emits events.
    /// </summary>
    struct AI_API Button : BaseComponent, SignalSource {
        Button(const FloatVector2 &pos, const FloatVector2 &sz = {100.f, 32.f})
            : BaseComponent(pos, sz) {
        }

        void draw(BaseApp *app) override;

        Color normal_color{0x1B, 0x24, 0x30};
        Color hover_color{0x51, 0x55, 0x7E};
        Color click_color{0x81, 0x67, 0x97};

      private:
        bool collides_with(IntVector2 point) {
            return (point.x >= position.x && point.x <= (position.x + size.x)) && (point.y >= position.y && point.y <= (position.y + size.y));
        }

        bool is_focused = false;
        bool is_clicked = false;

        void handle_mouse_state_event(void *ev);
        void handle_mouse_position_event(void *ev);

        QuadVertexBuffer<ColorVertex2D> vertices;
        bool is_first_frame = true;
    };
} // namespace ai_framework::components

#endif
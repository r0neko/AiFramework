#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <components/base_component.hpp>
#include <generic/signal_source.hpp>
#include <graphics/quad_vertex_buffer.hpp>
#include <graphics/texture.hpp>

namespace ai_framework::components {
    /// <summary>
    /// A clickable component that emits events.
    /// </summary>
    struct AI_API Button : BaseComponent, SignalSource {
        Button(const FloatVector2 &pos, const FloatVector2 &sz = {100.f, 32.f})
            : BaseComponent(pos, sz) {
        }

        void draw(BaseApp *app) override;

      private:
        bool collides_with(IntVector2 point) {
            return (point.x >= position.x && point.x <= (position.x + size.x)) && (point.y >= position.y && point.y <= (position.y + size.y));
        }

        Texture normal_texture{{"../AiFramework/assets/dank.png"}};
        void handle_mouse_state_event(void *ev);

        QuadVertexBuffer<TexturedVertex2D> vertices;
        bool is_first_frame = true;
    };
} // namespace ai_framework::components

#endif
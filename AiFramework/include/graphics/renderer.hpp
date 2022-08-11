#ifndef FRAMEWORK_RENDERER_HPP
#define FRAMEWORK_RENDERER_HPP

#include <framework_build.hpp>
#include <generic/singleton.hpp>
#include <generic/vector2.hpp>

namespace ai_framework::graphics {
    /// <summary>
    /// The renderer offers a simplified interface between the Graphical Pipeline and the app.
    /// </summary>
    struct AI_API Renderer {
        bool init(opaque_t dev_context, opaque_t extra, opaque_t extra2, const IntVector2 &size);
        void set_context(bool use_this = true);
        void destroy();
        void swap_buffers();

        bool is_init() const {
            return device_context != nullptr && render_context != GFX_OPAQUE_NULL;
        }

        void resize(const IntVector2 &new_size) {
            set_viewport(size = new_size);
            update_ortho();
        }

        void clear();
        void set_viewport(const IntVector2 &viewport);
        void update_ortho();

      private:
        IntVector2 size;
        opaque_t device_context{nullptr};
        opaque_t render_context{nullptr};
        gfx_opaque_t window_context{GFX_OPAQUE_NULL};
    };
} // namespace ai_framework::graphics

#endif
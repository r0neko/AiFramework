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
        bool init(opaque_t dev_context);
        void set_context(bool use_this = true);
        void destroy();
        void swap_buffers();

        bool is_init() const {
            return device_context != nullptr && render_context != nullptr;
        }

        void resize(const IntVector2 &new_size);

        void clear();
        void set_viewport(const IntVector2 &viewport);

      private:
        opaque_t device_context{nullptr};
        opaque_t render_context{nullptr};
    };
} // namespace ai_framework

#endif
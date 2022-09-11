#ifndef WGL_RENDERER_HPP
#define WGL_RENDERER_HPP

#include <graphics/gl_renderer.hpp>

using namespace ai_framework::graphics;

namespace ai_framework::platform::windows::graphics {
    struct AI_API WGLRenderer : GLRenderer {
        bool init(opaque_t dev_context, const IntVector2 &size) override;
        void set_context(bool use_this = true) override;
        void destroy() override;
        void swap_buffers() override;
        bool is_init() override;

      private:
        opaque_t device_context{nullptr};
        opaque_t render_context{nullptr};
    };
} // namespace ai_framework::platform::windows::graphics

#endif
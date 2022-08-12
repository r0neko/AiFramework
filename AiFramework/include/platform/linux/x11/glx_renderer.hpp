#ifndef WGL_RENDERER_HPP
#define WGL_RENDERER_HPP

#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xlib.h>

#include <framework_build.hpp>

#include <graphics/gl_renderer.hpp>

using namespace ai_framework::graphics;

namespace ai_framework::platform::linux::graphics {
    struct GLXRendererContext {
        Display *display;
        Window window;
        XVisualInfo *visual;
    };

    struct AI_API GLXRenderer : GLRenderer {
        bool init(opaque_t render_context, const IntVector2 &size) override;
        void set_context(bool use_this = true) override;
        void destroy() override;
        void swap_buffers() override;
        bool is_init() override;

      private:
        Display *display{nullptr};
        Window window = -1;
        GLXContext context{nullptr};
    };
} // namespace ai_framework::platform::linux::graphics

#endif
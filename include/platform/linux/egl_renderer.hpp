#ifndef EGL_RENDERER_HPP
#define EGL_RENDERER_HPP

#include <framework_build.hpp>
#include <graphics/gl_renderer.hpp>

#include <EGL/egl.h>

using namespace ai_framework::graphics;

namespace ai_framework::platform::linux_unix::graphics {
    struct AI_API EGLRenderer : GLRenderer {
        bool init(opaque_t render_context, const IntVector2 &size) override;
        void set_context(bool use_this = true) override;
        void destroy() override;
        void swap_buffers() override;
        bool is_init() override;
    private:
        EGLDisplay display{nullptr};
        EGLSurface surface{nullptr};
        EGLContext context{nullptr};
    };
} // namespace ai_framework::platform::linux::graphics

#endif
#ifndef DUMMY_RENDERER_HPP
#define DUMMY_RENDERER_HPP

#include <framework_build.hpp>

#include <graphics/gl_renderer.hpp>

using namespace ai_framework::graphics;

namespace ai_framework::platform::dummy::graphics {
    struct AI_API DummyRenderer : GLRenderer {
        bool init(opaque_t render_context, const IntVector2 &size) override { return true; }
        void set_context(bool use_this = true) override {}
        void destroy() override {}
        void swap_buffers() override {}
        bool is_init() override { return false; }
    };
} // namespace ai_framework::platform::dummy::graphics

#endif
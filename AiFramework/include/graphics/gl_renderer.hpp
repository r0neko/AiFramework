#ifndef GL_RENDERER_HPP
#define GL_RENDERER_HPP

#include <framework_build.hpp>

#include <graphics/i_renderer.hpp>

namespace ai_framework::graphics {
    /// <summary>
    /// Simple OpenGL interface for basic rendering.
    /// </summary>
    struct AI_API GLRenderer : IRenderer {
        void update_ortho() override;
        void clear() override;
        void resize(const IntVector2 &new_size) override;
        void set_viewport(const IntVector2 &viewport) override;
    };
} // namespace ai_framework::graphics

#endif
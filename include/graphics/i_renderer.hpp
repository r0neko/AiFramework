#ifndef FRAMEWORK_RENDERER_HPP
#define FRAMEWORK_RENDERER_HPP

#include <framework_build.hpp>
#include <generic/singleton.hpp>
#include <generic/vector2.hpp>

namespace ai_framework::graphics {
    /// <summary>
    /// Offers a simplified interface between the graphical renderer and the app.
    /// </summary>
    struct AI_API IRenderer {
        virtual bool init(opaque_t context, const IntVector2 &size) = 0;
        virtual void destroy() = 0;

        virtual bool is_init() = 0;

        virtual void resize(const IntVector2 &new_size) {
            size = new_size;
        };

        virtual void clear() = 0;
        virtual void set_context(bool use_this = true) = 0;
        virtual void set_viewport(const IntVector2 &viewport) = 0;
        virtual void update_ortho() = 0;
        virtual void swap_buffers() = 0;

      protected:
        IntVector2 size;
    };
} // namespace ai_framework::graphics

#endif
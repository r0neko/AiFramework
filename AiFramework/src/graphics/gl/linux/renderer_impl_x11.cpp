#ifdef _LINUX
#    ifdef _X11
#        include <framework/error_manager.hpp>
#        include <graphics/renderer.hpp>

#        include <glad/glad.h>

#        include <GL/glx.h>
#        include <X11/X.h>
#        include <X11/Xlib.h>

#        include <stdio.h>

using namespace ai_framework::graphics;
using namespace ai_framework::framework;

bool Renderer::init(opaque_t dev_context, opaque_t vi, opaque_t window, const IntVector2 &size) {
    device_context = dev_context;
    window_context = (gfx_opaque_t) window;

    render_context = glXCreateContext((Display *) dev_context, (XVisualInfo *) vi, NULL, 1);

    if (!render_context) {
        ErrorManager::instance().set_error(ErrorType::RENDERER_FAILURE, "Couldn't create a valid GLX context!");
        return false;
    }

    set_context();

    // load GL calls
    if (!gladLoadGL()) {
        ErrorManager::instance().set_error(ErrorType::RENDERER_FAILURE, "Failed to load OpenGL calls!");
        return false;
    }

    printf("Loaded OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);
    printf("OpenGL %s\n", glGetString(GL_VERSION));

    this->size = size;
    update_ortho();

    return is_init();
}

void Renderer::set_context(bool use_this) {
    if (!use_this)
        glXMakeCurrent((Display *) device_context, (Window) window_context, 0);
    else if (is_init())
        glXMakeCurrent((Display *) device_context, (Window) window_context, (GLXContext) render_context);
}

void Renderer::destroy() {
    set_context(0);

    render_context = nullptr;
    device_context = nullptr;
}

void Renderer::swap_buffers() {
    glXSwapBuffers((Display *) device_context, (Window) window_context);
}
#    endif
#endif
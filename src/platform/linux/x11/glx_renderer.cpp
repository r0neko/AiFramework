#ifdef _LINUX
#    ifdef _X11
#        include <glad/glad.h>
#        include <stdio.h>

#        include <framework/error_manager.hpp>
#        include <platform/linux/x11/glx_renderer.hpp>

using namespace ai_framework;
using namespace graphics;
using namespace framework;
using namespace platform::linux::graphics;

bool GLXRenderer::init(opaque_t param, const IntVector2 &size) {
    auto ctx = (GLXRendererContext *) param;

    display = ctx->display;
    window = ctx->window;

    context = glXCreateContext(display, ctx->visual, NULL, 1);

    if (!context) {
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

void GLXRenderer::set_context(bool use_this) {
    if (!use_this)
        glXMakeCurrent(display, window, 0);
    else if (is_init())
        glXMakeCurrent(display, window, context);
}

void GLXRenderer::destroy() {
    set_context(0);
    glXDestroyContext(display, context);
}

void GLXRenderer::swap_buffers() {
    glXSwapBuffers(display, window);
}

bool GLXRenderer::is_init() {
    return display != nullptr && context != nullptr && window != -1;
}
#    endif
#endif
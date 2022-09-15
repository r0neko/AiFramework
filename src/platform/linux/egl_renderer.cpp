#ifdef _EGL
#        include <stdio.h>
#        include <framework/error_manager.hpp>
#        include <platform/linux/egl_renderer.hpp>

#ifdef _ANDROID
#    include <GLES3/gl3.h>
#endif

using namespace ai_framework;
using namespace graphics;
using namespace framework;
using namespace platform::linux_unix::graphics;

bool EGLRenderer::init(opaque_t param, const IntVector2 &size) {
    const EGLint attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_NONE
    };
    EGLConfig config;
    EGLint numConfigs;
    EGLint format;
    ANativeWindow* _window;

    if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
        return false;
    }

    if (!eglInitialize(display, 0, 0)) {
        return false;
    }

    if (!eglChooseConfig(display, attribs, &config, 1, &numConfigs)) {
        return false;
    }

    if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format)) {
        return false;
    }

    if (!(surface = eglCreateWindowSurface(display, config, NULL, 0))) {
        return false;
    }

    if (!(context = eglCreateContext(display, config, 0, 0))) {
        return false;
    }

    set_context();

    this->size = size;
    update_ortho();

    return is_init();
}

void EGLRenderer::set_context(bool use_this) {
    if (!use_this)
        eglMakeCurrent(display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    else if (is_init())
        eglMakeCurrent(display, surface, surface, context);
}

void EGLRenderer::destroy() {
    set_context(0);
    eglDestroyContext(display, context);
    eglDestroySurface(display, surface);
    eglTerminate(display);
}

void EGLRenderer::swap_buffers() {
    eglSwapBuffers(display, surface);
}

bool EGLRenderer::is_init() {
    return display != nullptr && context != nullptr && surface != nullptr;
}
#endif
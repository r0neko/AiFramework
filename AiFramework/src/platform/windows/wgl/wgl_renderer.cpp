#ifdef _WINDOWS
#    include <framework/error_manager.hpp>
#    include <platform/windows/wgl/wglext.hpp>
#    include <platform/windows/wgl/wgl_renderer.hpp>

#    include <Windows.h>

#    include <glad/glad.h>
#    include <glad/glad_wgl.h>

#    include <stdio.h>

using namespace ai_framework::graphics;
using namespace ai_framework::platform::windows::graphics;
using namespace ai_framework::framework;

// TO DO: look at https://stackoverflow.com/questions/46655372/create-modern-opengl-context-using-wgl for an reference on how to properly init WGL

bool WGLRenderer::init(opaque_t dev_context, const IntVector2 &size) {
    PIXELFORMATDESCRIPTOR pfd{0};

    device_context = dev_context;

    // configure pixel format
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;

    if (!SetPixelFormat((HDC) device_context, ChoosePixelFormat((HDC) device_context, &pfd), &pfd)) {
        ErrorManager::instance().set_error(ErrorType::RENDERER_FAILURE, "Failed to configure the window Pixel Format");
        return false;
    }

    render_context = wglCreateContext((HDC) device_context);

    if (!render_context) {
        ErrorManager::instance().set_error(ErrorType::RENDERER_FAILURE, "Couldn't create a valid GL context!");
        return false;
    }

    set_context();

    if (!gladLoadWGL((HDC) device_context)) {
        ErrorManager::instance().set_error(ErrorType::RENDERER_FAILURE, "WGL couldn't be initialized!");
        return false;
    }

    int attr[] = {
        WGL_CONTEXT_FLAGS_ARB, 2,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0};

    auto wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC) wglGetProcAddress(
        "wglCreateContextAttribsARB");

    HGLRC new_render_context = wglCreateContextAttribsARB((HDC) device_context, NULL, attr);
    if (!new_render_context) {
        ErrorManager::instance().set_error(ErrorType::RENDERER_FAILURE, "Couldn't create a new valid GL3.2 context!");
        return false;
    }

    // destroy old context
    set_context(0);
    wglDeleteContext((HGLRC) render_context);

    // use new context
    render_context = new_render_context;
    set_context();

    // load GL calls
    if (!gladLoadGL()) {
        ErrorManager::instance().set_error(ErrorType::RENDERER_FAILURE, "Failed to load OpenGL calls!");
        return false;
    }

    printf("Loaded OpenGL %d.%d\n", GLVersion.major, GLVersion.minor);
    printf("OpenGL %s\n", glGetString(GL_VERSION));

    this->resize(size);

    return is_init();
}

void WGLRenderer::set_context(bool use_this) {
    if (!use_this)
        wglMakeCurrent(0, 0);
    else if (is_init())
        wglMakeCurrent((HDC) device_context, (HGLRC) render_context);
}

void WGLRenderer::destroy() {
    set_context(0);
    wglDeleteContext((HGLRC) render_context);

    render_context = nullptr;
    device_context = nullptr;
}

void WGLRenderer::swap_buffers() {
    if (is_init())
        SwapBuffers((HDC) device_context);
}

bool WGLRenderer::is_init() {
    return device_context != nullptr && render_context != nullptr;
}
#endif
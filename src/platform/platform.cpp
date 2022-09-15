#include <platform/platform.hpp>

#include <platform/dummy/dummy_app_window.hpp>
#include <platform/dummy/dummy_renderer.hpp>

#ifdef _WINDOWS
#    include <platform/windows/wgl/wgl_app_window.hpp>
#    include <platform/windows/wgl/wgl_renderer.hpp>
#elif _LINUX
#    ifdef _X11
#        include <platform/linux/x11/glx_app_window.hpp>
#        include <platform/linux/x11/glx_renderer.hpp>
#    endif
#endif

#ifdef _GL
#    include <platform/gl/open_gl_api.hpp>
#endif

#ifdef _EGL
#    include <platform/linux/egl_renderer.hpp>
#endif

using namespace ai_framework;

std::string_view platform::get_platform_name() {
#ifdef _WINDOWS
    return "Windows";
#elif _LINUX
    return "Linux";
#elif _ANDROID
    return "Android";
#else
    return "Unknown";
#endif
}

std::string_view platform::get_renderer_name() {
#ifdef _WIN32
    return "WGL";
#elif _LINUX
#    ifdef _X11
    return "X11/GLX";
#    endif
#elif _EGL
    return "EGL";
#else
    return "DummyRenderer";
#endif
}

std::string_view platform::get_graphics_api_name() {
#ifdef _GL
    return "OpenGL";
#else
    return "Unknown";
#endif
}

std::shared_ptr <framework::IAppWindow> platform::make_app_window() {
#ifdef _WIN32
    return std::make_shared<platform::windows::graphics::WGLAppWindow>();
#elif _LINUX
#    ifdef _X11
    return std::make_shared<platform::linux::graphics::GLXAppWindow>();
#    endif
#else
    return std::make_shared<platform::dummy::graphics::DummyAppWindow>();
#endif
}

std::shared_ptr <graphics::IRenderer> platform::make_renderer() {
#ifdef _WIN32
    return std::make_shared<platform::windows::graphics::WGLRenderer>();
#elif _LINUX
#    ifdef _X11
    return std::make_shared<platform::linux::graphics::GLXRenderer>();
#    endif
#elif _EGL
    return std::make_shared<platform::linux_unix::graphics::EGLRenderer>();
#else
    return std::make_shared<platform::dummy::graphics::DummyRenderer>();
#endif
}

std::shared_ptr <graphics::IGraphicsAPI> platform::make_graphics_api() {
#ifdef _GL
    return std::make_shared<api::OpenGLAPI>();
#else
    return {nullptr};
#endif
}
#include <platform/platform.hpp>

#ifdef _WIN32
#    include <platform/windows/wgl/wgl_app_window.hpp>
#    include <platform/windows/wgl/wgl_renderer.hpp>
#elif _LINUX
#    ifdef _X11
#        include <platform/linux/x11/glx_app_window.hpp>
#        include <platform/linux/x11/glx_renderer.hpp>
#    endif
#endif

using namespace ai_framework;

std::string_view platform::get_platform_name() {
#ifdef _WIN64
    return "64-bit Windows";
#elif _WIN32
    return "32-bit Windows";
#elif _LINUX
    return "Linux";
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
#else
    return "Unknown";
#endif
}

std::shared_ptr<framework::IAppWindow> platform::make_app_window() {
#ifdef _WIN32
    return std::make_shared<platform::windows::graphics::WGLAppWindow>();
#elif _LINUX
#    ifdef _X11
    return std::make_shared<platform::linux::graphics::GLXAppWindow>();
#    endif
#else
    return {nullptr};
#endif
}

std::shared_ptr<graphics::IRenderer> platform::make_renderer() {
#ifdef _WIN32
    return std::make_shared<platform::windows::graphics::WGLRenderer>();
#elif _LINUX
#    ifdef _X11
    return std::make_shared<platform::linux::graphics::GLXRenderer>();
#    endif
#else
    return {nullptr};
#endif
}
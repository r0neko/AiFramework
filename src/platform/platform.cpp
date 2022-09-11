#include <platform/platform.hpp>

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

using namespace ai_framework;

std::string_view platform::get_platform_name() {
#ifdef _WINDOWS
    return "Windows";
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

std::string_view platform::get_graphics_api_name() {
#ifdef _GL
    return "OpenGL";
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

std::shared_ptr<graphics::IGraphicsAPI> platform::make_graphics_api() {
#ifdef _GL
    return std::make_shared<api::OpenGLAPI>();
#else
    return {nullptr};
#endif
}
#include <platform/platform.hpp>

#ifdef _WIN32
#    include <platform/windows/wgl/wgl_app_window.hpp>
#    include <platform/windows/wgl/wgl_renderer.hpp>
#endif

using namespace ai_framework;

std::string_view platform::get_platform_name() {
#ifdef _WIN64
    return "64-bit Windows";
#elif _WIN32
    return "32-bit Windows";
#else
    return "Unknown";
#endif
}

std::string_view platform::get_renderer_name() {
#ifdef _WIN32
    return "WGL";
#else
    return "Unknown";
#endif
}

std::shared_ptr<framework::IAppWindow> platform::make_app_window() {
#ifdef _WIN32
    return std::make_shared<platform::windows::graphics::WGLAppWindow>();
#else
    return {nullptr};
#endif
}

std::shared_ptr<graphics::IRenderer> platform::make_renderer() {
#ifdef _WIN32
    return std::make_shared<platform::windows::graphics::WGLRenderer>();
#else
    return {nullptr};
#endif
}
#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <framework_build.hpp>

#include <memory>
#include <string>

#include <framework/i_app_window.hpp>
#include <graphics/i_graphics_api.hpp>
#include <graphics/i_renderer.hpp>

namespace ai_framework::platform {
    std::string_view AI_API get_platform_name();
    std::string_view AI_API get_renderer_name();
    std::string_view AI_API get_graphics_api_name();

    std::shared_ptr<framework::IAppWindow> AI_API make_app_window();
    std::shared_ptr<graphics::IRenderer> AI_API make_renderer();
    std::shared_ptr<graphics::IGraphicsAPI> AI_API make_graphics_api();
} // namespace ai_framework::platform

#endif
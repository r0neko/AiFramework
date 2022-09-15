// This is the main file of AiFramework

#ifdef _WIN32
#    include <Windows.h>
#endif

#include <ai_framework.hpp>

#include <framework/shaders_internal.hpp>
#include <generic/logger.hpp>
#include <graphics/graphics_api.hpp>
#include <platform/platform.hpp>
#include <shader_src.hpp>

#include <framework_config.hpp>

using namespace ai_framework;
using namespace graphics;
using namespace shaders;

CLogger _fwk_logger("AiFramework");

void ai_framework::shader_init() {
    if (vertex_2d_shader.compiled() && color_vertex_2d_shader.compiled())
        return;

    // don't load this 100 times! load it only once
    Shader color_v2d_fragment{"ColorVertex2D", shaders::sources::ColorVertex2D_Fragment,
                              ShaderType::FRAGMENT};
    // auto color_v2d_fragment = Shader::from_file("ColorVertex2D", "./shader/ColorVertex2D.fs", ShaderType::FRAGMENT);

    if (!vertex_2d_shader.compiled()) {
        _fwk_logger.log(LoggerLevel::DEBUG, "Vertex2D shader compilation...");

        vertex_2d_shader.add_shader(color_v2d_fragment);
        vertex_2d_shader.add_shader({"Vertex2D", shaders::sources::Vertex2D_Vertex, ShaderType::VERTEX});
        //        vertex_2d_shader.add_shader(Shader::from_file("Vertex2D", "./shader/Vertex2D.vs", ShaderType::VERTEX));

        if (vertex_2d_shader.compile())
            _fwk_logger.log(LoggerLevel::DEBUG, "Vertex2D was compiled!");
        else
            _fwk_logger.log(LoggerLevel::DEBUG, "Failed to compile the Vertex2D shader!");
    }

    if (!color_vertex_2d_shader.compiled()) {
        _fwk_logger.log(LoggerLevel::DEBUG, "ColorVertex2D shader compilation...");

        color_vertex_2d_shader.add_shader(color_v2d_fragment);
        color_vertex_2d_shader.add_shader(
            {"ColorVertex2D", shaders::sources::ColorVertex2D_Vertex, ShaderType::VERTEX});
        //        color_vertex_2d_shader.add_shader(Shader::from_file("ColorVertex2D", "./shader/ColorVertex2D.vs", ShaderType::VERTEX));

        if (color_vertex_2d_shader.compile())
            _fwk_logger.log(LoggerLevel::DEBUG, "ColorVertex2D was compiled!");
        else
            _fwk_logger.log(LoggerLevel::DEBUG, "Failed to compile the ColorVertex2D shader!");
    }

    if (!textured_vertex_2d_shader.compiled()) {
        _fwk_logger.log(LoggerLevel::DEBUG, "TexturedVertex2D shader compilation...");

        textured_vertex_2d_shader.add_shader(
            {"TexturedVertex2D", shaders::sources::TexturedVertex2D_Fragment, ShaderType::FRAGMENT});
        textured_vertex_2d_shader.add_shader(
            {"TexturedVertex2D", shaders::sources::TexturedVertex2D_Vertex, ShaderType::VERTEX});

        //        textured_vertex_2d_shader.add_shader(
        //                Shader::from_file("TexturedVertex2D", "./shader/TexturedVertex2D.fs",
        //                                  ShaderType::FRAGMENT));
        //        textured_vertex_2d_shader.add_shader(
        //                Shader::from_file("TexturedVertex2D", "./shader/TexturedVertex2D.vs",
        //                                  ShaderType::VERTEX));

        if (textured_vertex_2d_shader.compile())
            _fwk_logger.log(LoggerLevel::DEBUG, "TexturedVertex2D was compiled!");
        else
            _fwk_logger.log(LoggerLevel::DEBUG, "Failed to compile the TexturedVertex2D shader!");
    }
}

void ai_framework::init() {
    _fwk_logger.log(LoggerLevel::DEBUG,
                    "+----------------------------------------------------------------------------+");
    _fwk_logger.log(LoggerLevel::DEBUG, "| Welcome to AiFramework %s!", config::version::to_string().c_str());
    _fwk_logger.log(LoggerLevel::DEBUG, "| Running on %s using %s as a renderer and %s API.",
                    platform::get_platform_name().data(), platform::get_renderer_name().data(),
                    platform::get_graphics_api_name().data());
    _fwk_logger.log(LoggerLevel::DEBUG,
                    "+----------------------------------------------------------------------------+");

    if (graphics::api == nullptr) {
        _fwk_logger.log(LoggerLevel::DEBUG, "Graphics API not initialized! Will initialize now!");
        graphics::api = platform::make_graphics_api();
    }
}

void ai_framework::unload() {
    _fwk_logger.log(LoggerLevel::DEBUG,
                    "+----------------------------------------------------------------------------+");
    _fwk_logger.log(LoggerLevel::DEBUG,
                    "| AiFramework unloading...                                                   |");
    _fwk_logger.log(LoggerLevel::DEBUG,
                    "+----------------------------------------------------------------------------+");
}

#ifdef _WIN32

bool WINAPI DllMain(HINSTANCE, DWORD reason, opaque_t) {

    switch (reason) {
    case DLL_PROCESS_DETACH:
        ai_framework::unload();
        break;
    case DLL_PROCESS_ATTACH:
        ai_framework::init();
        break;
    }

    return true;
}

#else

void __attribute__((constructor)) startup() {
    ai_framework::init();
}

void __attribute__((destructor)) shutdown() {
    ai_framework::unload();
}

#endif
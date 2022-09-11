// This is the main file of AiFramework

#ifdef _WIN32
#    include <Windows.h>
#endif

#include <ai_framework.hpp>
#include <framework/shaders_internal.hpp>
#include <platform/platform.hpp>

#include <graphics/graphics_api.hpp>

#include <generic/logger.hpp>

using namespace ai_framework;
using namespace graphics;
using namespace shaders;

CLogger _fwk_logger("AiFramework");

void ai_framework::shader_init() {
    if (vertex_2d_shader.compiled() && color_vertex_2d_shader.compiled())
        return;

    // don't load this 100 times! load it only once
    auto color_v2d_fragment = Shader::from_file("ColorVertex2D", "../AiFramework/shader/ColorVertex2D.fs", ShaderType::FRAGMENT);

    if (!vertex_2d_shader.compiled()) {
        _fwk_logger.log(LoggerLevel::DEBUG, "Vertex2D shader compilation...");

        vertex_2d_shader.add_shader(color_v2d_fragment);
        vertex_2d_shader.add_shader(Shader::from_file("Vertex2D", "../AiFramework/shader/Vertex2D.vs", ShaderType::VERTEX));

        if (vertex_2d_shader.compile())
            _fwk_logger.log(LoggerLevel::DEBUG, "Vertex2D was compiled!");
        else
            _fwk_logger.log(LoggerLevel::DEBUG, "Failed to compile the Vertex2D shader!");
    }

    if (!color_vertex_2d_shader.compiled()) {
        _fwk_logger.log(LoggerLevel::DEBUG, "ColorVertex2D shader compilation...");

        color_vertex_2d_shader.add_shader(color_v2d_fragment);
        color_vertex_2d_shader.add_shader(Shader::from_file("ColorVertex2D", "../AiFramework/shader/ColorVertex2D.vs", ShaderType::VERTEX));

        if (color_vertex_2d_shader.compile())
            _fwk_logger.log(LoggerLevel::DEBUG, "ColorVertex2D was compiled!");
        else
            _fwk_logger.log(LoggerLevel::DEBUG, "Failed to compile the ColorVertex2D shader!");
    }

    if (!textured_vertex_2d_shader.compiled()) {
        _fwk_logger.log(LoggerLevel::DEBUG, "TexturedVertex2D shader compilation...");

        textured_vertex_2d_shader.add_shader(Shader::from_file("TexturedVertex2D", "../AiFramework/shader/TexturedVertex2D.fs", ShaderType::FRAGMENT));
        textured_vertex_2d_shader.add_shader(Shader::from_file("TexturedVertex2D", "../AiFramework/shader/TexturedVertex2D.vs", ShaderType::VERTEX));

        if (textured_vertex_2d_shader.compile())
            _fwk_logger.log(LoggerLevel::DEBUG, "TexturedVertex2D was compiled!");
        else
            _fwk_logger.log(LoggerLevel::DEBUG, "Failed to compile the TexturedVertex2D shader!");
    }
}

void ai_framework::init() {
    _fwk_logger.log(LoggerLevel::DEBUG, "+----------------------------------------------------------------------------+");
    _fwk_logger.log(LoggerLevel::DEBUG, "| Welcome to AiFramework!");
    _fwk_logger.log(LoggerLevel::DEBUG, "| Running on %s using %s as a renderer and %s API.", platform::get_platform_name().data(), platform::get_renderer_name().data(), platform::get_graphics_api_name().data());
    _fwk_logger.log(LoggerLevel::DEBUG, "+----------------------------------------------------------------------------+");

    if (graphics::api == nullptr) {
        _fwk_logger.log(LoggerLevel::DEBUG, "Graphics API not initialized! Will initialize now!");
        graphics::api = platform::make_graphics_api();
    }
}

void ai_framework::unload() {
    _fwk_logger.log(LoggerLevel::DEBUG, "+----------------------------------------------------------------------------+");
    _fwk_logger.log(LoggerLevel::DEBUG, "| AiFramework unloading...                                                   |");
    _fwk_logger.log(LoggerLevel::DEBUG, "+----------------------------------------------------------------------------+");
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

#endif
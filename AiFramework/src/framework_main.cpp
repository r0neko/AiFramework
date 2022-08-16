// This is the main file of AiFramework

#ifdef _WIN32
#    include <Windows.h>
#endif

#include <ai_framework.hpp>
#include <framework/shaders_internal.hpp>
#include <platform/platform.hpp>

#include <graphics/graphics_api.hpp>

using namespace ai_framework::graphics;
using namespace ai_framework::shaders;

void ai_framework::shader_init() {
    if (vertex_2d_shader.compiled() && color_vertex_2d_shader.compiled())
        return;

    // don't load this 100 times! load it only once
    auto color_v2d_fragment = Shader::from_file("ColorVertex2D", "../AiFramework/shader/ColorVertex2D.fs", ShaderType::FRAGMENT);

    if (!vertex_2d_shader.compiled()) {
        printf("Vertex2D shader compilation...\n");

        vertex_2d_shader.add_shader(color_v2d_fragment);
        vertex_2d_shader.add_shader(Shader::from_file("Vertex2D", "../AiFramework/shader/Vertex2D.vs", ShaderType::VERTEX));

        if (vertex_2d_shader.compile())
            printf("Vertex2D was compiled!\n");
        else
            printf("Failed to compile the Vertex2D shader!\n");
    }

    if (!color_vertex_2d_shader.compiled()) {
        printf("ColorVertex2D shader compilation...\n");

        color_vertex_2d_shader.add_shader(color_v2d_fragment);
        color_vertex_2d_shader.add_shader(Shader::from_file("ColorVertex2D", "../AiFramework/shader/ColorVertex2D.vs", ShaderType::VERTEX));

        if (color_vertex_2d_shader.compile())
            printf("ColorVertex2D was compiled!\n");
        else
            printf("Failed to compile the ColorVertex2D shader!\n");
    }

    if (!textured_vertex_2d_shader.compiled()) {
        printf("TexturedVertex2D shader compilation...\n");

        textured_vertex_2d_shader.add_shader(Shader::from_file("TexturedVertex2D", "../AiFramework/shader/TexturedVertex2D.fs", ShaderType::FRAGMENT));
        textured_vertex_2d_shader.add_shader(Shader::from_file("TexturedVertex2D", "../AiFramework/shader/TexturedVertex2D.vs", ShaderType::VERTEX));

        if (textured_vertex_2d_shader.compile())
            printf("TexturedVertex2D was compiled!\n");
        else
            printf("Failed to compile the TexturedVertex2D shader!\n");
    }
}

void ai_framework::init() {
    printf("+----------------------------------------------------------------------------+\n");
    printf("| Welcome to AiFramework!\n");
    printf("| Running on %s using %s as a renderer and %s API.\n", platform::get_platform_name().data(), platform::get_renderer_name().data(), platform::get_graphics_api_name().data());
    printf("+----------------------------------------------------------------------------+\n");

    if (graphics::api == nullptr) {
        printf("Graphics API not initialized! Will initialize now!\n");
        graphics::api = platform::make_graphics_api();
    }
}

void ai_framework::unload() {
    printf("+----------------------------------------------------------------------------+\n");
    printf("| AiFramework unloading...                                                   |\n");
    printf("+----------------------------------------------------------------------------+\n");
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
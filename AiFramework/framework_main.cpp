// bootstrap file to compile everything

#include <ai_framework.hpp>
#include <framework/shaders_internal.hpp>

using namespace ai_framework::graphics;
using namespace ai_framework::shaders;

void ai_framework::init() {
    if (vertex_2d_shader.compiled() && color_vertex_2d_shader.compiled())
        return;

    // don't load this 100 times! load it only once
    auto color_v2d_fragment = Shader::from_file("ColorVertex2D", "E:/PROGRAME CSARP/AiEngine/AiFramework/shader/ColorVertex2D.fs", ShaderType::FRAGMENT);

    if (!vertex_2d_shader.compiled()) {
        printf("Vertex2D shader compilation...\n");

        vertex_2d_shader.add_shader(color_v2d_fragment);
        vertex_2d_shader.add_shader(Shader::from_file("Vertex2D", "E:/PROGRAME CSARP/AiEngine/AiFramework/shader/Vertex2D.vs", ShaderType::VERTEX));

        if (vertex_2d_shader.compile())
            printf("Vertex2D was compiled!\n");
        else
            printf("Failed to compile the Vertex2D shader!\n");
    }

    if (!color_vertex_2d_shader.compiled()) {
        printf("ColorVertex2D shader compilation...\n");

        color_vertex_2d_shader.add_shader(color_v2d_fragment);
        color_vertex_2d_shader.add_shader(Shader::from_file("ColorVertex2D", "E:/PROGRAME CSARP/AiEngine/AiFramework/shader/ColorVertex2D.vs", ShaderType::VERTEX));

        if (color_vertex_2d_shader.compile())
            printf("ColorVertex2D was compiled!\n");
        else
            printf("Failed to compile the ColorVertex2D shader!\n");
    }
}
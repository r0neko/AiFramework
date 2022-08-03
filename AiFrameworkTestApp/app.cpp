#include <ai_framework.hpp>

using namespace ai_framework::framework;
using namespace ai_framework::graphics;

struct TestApp : BaseApp {
    TestApp()
        : s_text_2d("2DTexture") {
    }

    bool start() override {
        printf("App start!\n");

        s_text_2d.add_shader(Shader::from_file("2DTexture", "../AiFramework/shader/2DTexture.fs", ShaderType::FRAGMENT));
        s_text_2d.add_shader(Shader::from_file("2DTexture", "../AiFramework/shader/2DTexture.vs", ShaderType::VERTEX));

        vertex_quad.add_2d_vertex({0.5f, 0.5f, colors::green});   // top right
        vertex_quad.add_2d_vertex({0.5f, -0.5f, colors::white});  // bottom right
        vertex_quad.add_2d_vertex({-0.5f, -0.5f, colors::blue}); // bottom left
        vertex_quad.add_2d_vertex({-0.5f, 0.5f, colors::red});  // top left

        vertex_quad.create();
        vertex_quad.resize();

        return s_text_2d.compile();
    }

    void draw() override {
        window.renderer.set_context();
        window.renderer.clear();

        s_text_2d.use();

        vertex_quad.draw();

        window.renderer.swap_buffers();
    }

    ShaderProgram s_text_2d;
    QuadVertexBuffer vertex_quad;
};

int main() {
    TestApp app;

    if (!app.init()) {
        ErrorManager::instance().print_error();
        return -1;
    }

    app.run();
    app.destroy();

    return 0;
}
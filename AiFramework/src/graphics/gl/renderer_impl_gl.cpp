#include <graphics/renderer.hpp>
#include <graphics/shader_program.hpp>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// dirty hack incoming!
#include <framework/shaders_internal.hpp>

using namespace ai_framework;
using namespace ai_framework::graphics;

void Renderer::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::update_ortho() {
    printf("update ortho!\n");
    auto ortho = glm::orthoZO(0.f, (float) size.x, (float) size.y, 0.f, -1.f, 1.f);

    // dirty hack for now
    if (shaders::vertex_2d_shader.compiled())
        shaders::vertex_2d_shader.set("uProjMatrix", ortho);

    if (shaders::color_vertex_2d_shader.compiled())
        shaders::color_vertex_2d_shader.set("uProjMatrix", ortho);

    if (shaders::textured_vertex_2d_shader.compiled())
        shaders::textured_vertex_2d_shader.set("uProjMatrix", ortho);
}

void Renderer::set_viewport(const IntVector2 &viewport) {
    printf("Renderer viewport set to %ix%i\n", viewport.x, viewport.y);
    glViewport(0, 0, viewport.x, viewport.y);
}
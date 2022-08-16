#include <graphics/gl_renderer.hpp>
#include <graphics/shader_program.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// dirty hack incoming!
#include <framework/shaders_internal.hpp>
#include <graphics/graphics_api.hpp>

using namespace ai_framework;
using namespace ai_framework::graphics;

void GLRenderer::clear() {
    api->set_clear_color(colors::black);
    api->clear();
}

void GLRenderer::update_ortho() {
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

void GLRenderer::set_viewport(const IntVector2 &viewport) {
    printf("GLRenderer viewport set to %ix%i\n", viewport.x, viewport.y);
    api->set_viewport(viewport);
}

void GLRenderer::resize(const IntVector2 &new_size) {
    set_viewport(size = new_size);
    update_ortho();
}
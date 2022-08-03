#include <graphics/renderer.hpp>

#include <glad/glad.h>

using namespace ai_framework::graphics;

void Renderer::clear() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::set_viewport(const IntVector2 &viewport) {
    glViewport(0, 0, viewport.x, viewport.y);
}
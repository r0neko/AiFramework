#include <components/button.hpp>

using namespace ai_framework::components;

void Button::draw(BaseApp *app) {
    if (is_first_frame) {
        app->window.input_manager.listen("mouse_state_update", [&](void *param) {
            handle_mouse_state_event(param);
        });

        is_first_frame = false;
    }

    if (!vertices.can_render()) {
        vertices.clear();

        vertices.add_vertex({position.x + size.x, position.y, color, 1.0f, 1.0f});          // top right
        vertices.add_vertex({position.x + size.x, position.y + size.y, color, 1.0f, 0.0f}); // bottom right
        vertices.add_vertex({position.x, position.y + size.y, color, 0.0f, 0.0f});          // bottom left
        vertices.add_vertex({position, color, {0.0f, 1.0f}});                               // top left
    }

    // textured vertex rendering
    // quad_buffer.add_vertex({0.5f, 0.5f, colors::red, 1.0f, 1.0f});    // top right
    // quad_buffer.add_vertex({0.5f, -0.5f, colors::green, 1.0f, 0.0f}); // bottom right
    // quad_buffer.add_vertex({-0.5f, -0.5f, colors::blue, 0.0f, 0.0f}); // bottom left
    // quad_buffer.add_vertex({-0.5f, 0.5f, colors::white, 0.0f, 1.0f}); // top left

    normal_texture.use();
    vertices.draw();
}

void Button::handle_mouse_state_event(void *param) {
    auto ev = (MouseStateEventParam *) param;

    if ((ev->old_buttons & ButtonState::MOUSE_LEFT) > 0) {
        // greatest cursor collision system!
        if (collides_with(ev->position)) {
            emit("click", 0);
        }
    }
}
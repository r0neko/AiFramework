#include <components/button.hpp>

using namespace ai_framework::components;

void Button::draw(BaseApp *app) {
    if (is_first_frame) {
        app->window->input_manager.listen("mouse_state_update", [&](void *param) {
            handle_mouse_state_event(param);
        });

        app->window->input_manager.listen("mouse_position_update", [&](void *param) {
            handle_mouse_position_event(param);
        });

        is_first_frame = false;
    }

    auto &color = is_focused ? (is_clicked ? click_color : hover_color) : normal_color;

    vertices.clear();

    vertices.add_vertex({position.x + size.x, position.y, color});          // top right
    vertices.add_vertex({position.x + size.x, position.y + size.y, color}); // bottom right
    vertices.add_vertex({position.x, position.y + size.y, color});          // bottom left
    vertices.add_vertex({position, color});                                 // top left

    vertices.draw();
}

void Button::handle_mouse_position_event(void *param) {
    auto ev = (MousePositionEventParam *) param;

    if (collides_with(ev->position)) {
        is_focused = true;
    } else if ((ev->buttons & ButtonState::MOUSE_LEFT) <= 0)
        is_focused = false;
}

void Button::handle_mouse_state_event(void *param) {
    auto ev = (MouseStateEventParam *) param;

    if ((ev->old_buttons & ButtonState::MOUSE_LEFT) > 0) {
        // greatest cursor collision system!
        if (collides_with(ev->position)) {
            emit("click", 0);
        }

        is_clicked = false;
    }

    if ((ev->buttons & ButtonState::MOUSE_LEFT) > 0) {
        is_clicked = true;
    }
}
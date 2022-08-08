#include <ai_framework.hpp>

using namespace ai_framework::framework;
using namespace ai_framework::graphics;
using namespace ai_framework::components;

struct TestApp : BaseApp {
    bool start() override {
        printf("App start!\n");

        window.input_manager.listen("mouse_state_update", [&](void *param) {
            input_click_up_callback(param);
        });

        return true;
    }

    void input_click_up_callback(void *param) {
        auto ev = (MouseStateEventParam *) param;

        if ((ev->old_buttons & ButtonState::MOUSE_LEFT) > 0) {
            printf("click up at %ix%i\n", ev->position.x, ev->position.y);
            colection.push_back({{(float) ev->position.x, (float) ev->position.y}, {10.f, 10.f}, colors::green});
        }
    }

    // WASD to move the white square
    // red/green/blue/white square for cursor, use left-right-both mouse buttons to see it working
    void draw() override {
        auto cursor = window.input_manager.get_position_float();

        cursor_rect.position = cursor;

        if (window.input_manager.has_button(ButtonState::MOUSE_LEFT) && window.input_manager.has_button(ButtonState::MOUSE_RIGHT))
            cursor_rect.color = colors::white;
        else if (window.input_manager.has_button(ButtonState::MOUSE_LEFT))
            cursor_rect.color = colors::green;
        else if (window.input_manager.has_button(ButtonState::MOUSE_RIGHT))
            cursor_rect.color = colors::blue;
        else
            cursor_rect.color = colors::red;

        if (window.input_manager.get_key_state(KeyType::KEY_W))
            test_rect.position.y -= 1.f;
        else if (window.input_manager.get_key_state(KeyType::KEY_S))
            test_rect.position.y += 1.f;

        if (window.input_manager.get_key_state(KeyType::KEY_A))
            test_rect.position.x -= 1.f;
        else if (window.input_manager.get_key_state(KeyType::KEY_D))
            test_rect.position.x += 1.f;

        test_rect.draw();

        for (auto &a : colection)
            a.draw();

        cursor_rect.draw();
    }

    RectangleComponent cursor_rect{{0.f, 0.f}, {12.f, 18.f}, colors::red};
    RectangleComponent test_rect{{100.f, 100.f}, {60.f, 60.f}, colors::white};
    std::vector<RectangleComponent> colection;
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
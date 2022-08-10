#include <ai_framework.hpp>

using namespace ai_framework::framework;
using namespace ai_framework::graphics;
using namespace ai_framework::components;

struct TestApp : BaseApp {
    bool start() override {
        printf("App start!\n");

        window.input_manager.listen("mouse_state_update", [&](void *param) {
            auto ev = (MouseStateEventParam *) param;

            if ((ev->old_buttons & ButtonState::MOUSE_LEFT) > 0)
                colection.push_back({{(float) ev->position.x, (float) ev->position.y}, {10.f, 10.f}, colors::green});

            if ((ev->buttons & ButtonState::MOUSE_LEFT) > 0 && (ev->buttons & ButtonState::MOUSE_RIGHT) > 0)
                cursor_rect.color = colors::white;
            else if ((ev->buttons & ButtonState::MOUSE_LEFT) > 0)
                cursor_rect.color = colors::green;
            else if ((ev->buttons & ButtonState::MOUSE_RIGHT) > 0)
                cursor_rect.color = colors::blue;
            else
                cursor_rect.color = colors::red;
        });

        window.input_manager.listen("mouse_position_update", [&](void *param) {
            auto ev = (MousePositionEventParam *) param;
            cursor_rect.position = {(float) ev->position.x, (float) ev->position.y};
        });

        window.input_manager.listen("key_update", [&](void *param) {
            auto ev = (KeyUpdateEventParam *) param;

            if (ev->pressed) {
                switch (ev->key) {
                default: break;
                case KeyType::KEY_W:
                    rect_units.y = -1.f;
                    break;
                case KeyType::KEY_S:
                    rect_units.y = 1.f;
                    break;
                }
            } else
                rect_units.y = 0.f;

            if (ev->pressed) {
                switch (ev->key) {
                default: break;
                case KeyType::KEY_A:
                    rect_units.x = -1.f;
                    break;
                case KeyType::KEY_D:
                    rect_units.x = 1.f;
                    break;
                }
            } else
                rect_units.x = 0.f;
        });

        test_btn.listen("click", [&](void *) {
            printf("doing some cleaning! we have to kill %zi components\n", colection.size());
            colection.clear();
        });

        return true;
    }

    // WASD to move the white square
    // red/green/blue/white square for cursor, use left-right-both mouse buttons to see it working
    void draw(BaseApp *app) override {
        test_rect.position += rect_units;

        test_rect.draw(app);
        test_btn.draw(app);

        for (auto &a : colection)
            a.draw(app);

        cursor_rect.draw(app);
    }

    RectangleComponent cursor_rect{{0.f, 0.f}, {12.f, 18.f}, colors::red};
    RectangleComponent test_rect{{100.f, 100.f}, {60.f, 60.f}, colors::white};
    Button test_btn{{10.f, 10.f}};

    std::vector<RectangleComponent> colection;

    FloatVector2 rect_units;
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
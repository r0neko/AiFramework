#include <ai_framework.hpp>

using namespace ai_framework::framework;
using namespace ai_framework::graphics;
using namespace ai_framework::components;

struct TestApp : BaseApp {
    bool start() override {
        printf("App start!\n");
        ai_framework::init();
        return true;
    }

    void draw() override {
        window.renderer.set_context();
        window.renderer.clear();

        rect_component.draw();

        window.renderer.swap_buffers();
    }

    RectangleComponent rect_component;
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
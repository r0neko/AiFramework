#include <ai_framework.hpp>

using namespace ai_framework::framework;
using namespace ai_framework::graphics;
using namespace ai_framework::components;

struct TestApp : BaseApp {
    bool start() override {
        printf("App start!\n");
        return true;
    }

    void draw() override {
        rect.draw();
        rect2.draw();
        rect3.draw();
    }

    RectangleComponent rect{{100.f, 100.f}, {100.f, 200.f}, colors::blue};
    RectangleComponent rect2{{200.f, 100.f}, {100.f, 200.f}, colors::yellow};
    RectangleComponent rect3{{300.f, 100.f}, {100.f, 200.f}, colors::red};
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
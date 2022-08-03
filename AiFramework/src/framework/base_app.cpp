#include <framework/base_app.hpp>

using namespace ai_framework::framework;

bool BaseApp::init() {
    if (window.is_init() || !window.init())
        return false;
    return true;
}

void BaseApp::run() {
    if (!start())
        return;

    while (!window.is_quit_queued()) {
        window.process_events();
        draw();
    }
}

void BaseApp::destroy() {
    if (window.is_init())
        window.destroy();
}
#include <framework/base_app.hpp>
#include <framework_main.hpp>
#include <platform/platform.hpp>

using namespace ai_framework;
using namespace ai_framework::framework;

bool BaseApp::init() {
    if (!window)
        window = platform::make_app_window();

    if (!window || window->is_init() || !window->init())
        return false;

    return true;
}

void BaseApp::_render() {
    // pre rendering
    window->renderer->set_context();
    window->renderer->clear();

    // real drawing
    draw(this);

    // swap buffers
    window->renderer->swap_buffers();
}

void BaseApp::run() {
    ai_framework::init();

    if (!start())
        return;

    window->renderer->resize(window->get_size());
    window->show();

    while (!window->is_quit_queued()) {
        window->process_events();
        _render();
    }
}

void BaseApp::destroy() {
    if (window->is_init())
        window->destroy();

    window = nullptr;
}
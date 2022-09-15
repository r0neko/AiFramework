#ifndef DUMMY_APP_WINDOW_HPP
#define DUMMY_APP_WINDOW_HPP

#include <framework_build.hpp>
#include <framework/i_app_window.hpp>

#include <string>

namespace ai_framework::platform::dummy::graphics {
    struct AI_API DummyAppWindow : framework::IAppWindow {
        bool init() override { return true; }
        void destroy() override {}
        void process_events() override {}
        void show() override {}
        void set_title(std::string_view new_title) override {}
        bool is_init() override { return false; }
    };
} // namespace ai_framework::platform::dummy::graphics

#endif
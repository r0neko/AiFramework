#ifndef X11_APP_WINDOW_HPP
#define X11_APP_WINDOW_HPP

#include <GL/glx.h>
#include <X11/X.h>
#include <X11/Xlib.h>

#include <framework_build.hpp>

#include <framework/i_app_window.hpp>

#include <string>
#include <thread>

namespace ai_framework::platform::linux::graphics {
    struct AI_API GLXAppWindow : framework::IAppWindow {
        bool init() override;
        void destroy() override;
        void process_events() override;
        void show() override;
        void set_title(std::string_view new_title) override;
        bool is_init() override;

      private:
        Display *display{nullptr};
        Window window;
        std::thread input_thread;
    };
} // namespace ai_framework::platform::linux::graphics

#endif
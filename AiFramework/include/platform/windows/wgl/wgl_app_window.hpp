#ifndef WGL_APP_WINDOW_HPP
#define WGL_APP_WINDOW_HPP

#include <framework/i_app_window.hpp>

namespace ai_framework::platform::windows::graphics {
    struct AI_API WGLAppWindow : framework::IAppWindow {
        bool init() override;
        void destroy() override;
        void process_events() override;
        void show() override;
        void set_title(std::string_view new_title) override;
        bool is_init() override;

      private:
        std::string win_class = "AI_FRAMEWORK_WIN_CLASS";
        opaque_t window_handle{nullptr};
    };
} // namespace ai_framework::platform::windows::graphics

#endif
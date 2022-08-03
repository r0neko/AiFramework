#ifndef APP_WINDOW_HPP
#define APP_WINDOW_HPP

#include <framework_build.hpp>

#include <generic/vector2.hpp>
#include <graphics/renderer.hpp>

#include <string>

using namespace ai_framework::graphics;

namespace ai_framework::framework {
    /// <summary>
    /// An application window with a renderer.
    /// </summary>
    struct AI_API AppWindow {
        bool init();
        void destroy();
        void process_events();

        void set_title(std::string_view new_title);

        bool is_quit_queued() const {
            return quit_queued;
        }

        bool is_init() const {
            return window_handle != nullptr;
        }

        virtual void resize(const IntVector2 &new_resolution) {
            size = new_resolution;
            renderer.resize(size);
        }

        Renderer renderer;

      protected:
        IntVector2 size{800, 600};

        std::string win_class = "AI_FRAMEWORK_WIN_CLASS";
        std::string title = "AiFramework";

      private:
        bool quit_queued = false;
        opaque_t window_handle{nullptr};
    };
} // namespace ai_framework::framework

#endif
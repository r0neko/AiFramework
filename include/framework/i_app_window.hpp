#ifndef APP_WINDOW_HPP
#define APP_WINDOW_HPP

#include <framework_build.hpp>

#include <generic/vector2.hpp>
#include <graphics/i_renderer.hpp>
#include <input/input_manager.hpp>

#include <string>

using namespace ai_framework::graphics;
using namespace ai_framework::input;

namespace ai_framework::framework {
    struct AI_API IAppWindow {
        virtual bool init() = 0;
        virtual void destroy() = 0;
        virtual void process_events() = 0;
        virtual void show() = 0;

        virtual void set_title(std::string_view new_title) = 0;

        bool is_quit_queued() const {
            return quit_queued;
        }

        virtual bool is_init() = 0;

        virtual void resize(const IntVector2 &new_resolution) {
            size = new_resolution;

            if (renderer)
                renderer->resize(size);
        }

        IntVector2 get_size() const {
            return size;
        }

        std::shared_ptr<IRenderer> renderer{nullptr};
        InputManager input_manager;

      protected:
        IntVector2 size{800, 600};
        std::string title = "AiFramework";

        bool quit_queued = true;
    };
} // namespace ai_framework::framework

#endif
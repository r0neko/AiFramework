#ifndef BASE_APP_HPP
#define BASE_APP_HPP

#include <framework/i_app_window.hpp>
#include <framework_build.hpp>

#include <generic/vector2.hpp>

#include <memory>
#include <string>

namespace ai_framework::framework {
    /// <summary>
    /// Base App class to be extended by future apps that will use AiFramework.
    /// </summary>
    struct AI_API BaseApp {
        bool init();
        void destroy();
        void run();

        virtual void draw(BaseApp *app) = 0;

        std::shared_ptr<IAppWindow> window{nullptr};

      protected:
        virtual bool start() {
            return true;
        };

        void _render();
    };
} // namespace ai_framework::framework

#endif
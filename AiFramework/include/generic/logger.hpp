#ifndef LOGGER_H
#define LOGGER_H

#pragma warning(push)
#pragma warning(disable : 4251)

#include <cstdarg>
#include <cstdio>
#include <framework_build.hpp>
#include <string_view>

namespace ai_framework {
    enum LoggerLevel {
        UNKNOWN,
        DEBUG,
        INFO,
        ERR
    };

    struct AI_API CLogger {
        CLogger(std::string_view _identifier)
            : identifier(_identifier) {
        }

        // log a message to the console
        void log(LoggerLevel level, std::string_view tmp, va_list args);
        void log(LoggerLevel level, std::string_view tmp, ...);

      private:
        std::string_view identifier;
    };
} // namespace ai_framework

#pragma warning(pop)

#endif
#include <generic/logger.hpp>

#ifdef _ANDROID
#include <android/log.h>
#include <cstdio>
#endif

using namespace ai_framework;

std::string_view logger_level_to_string(LoggerLevel level) {
    switch (level) {
        default:
        case UNKNOWN:
            return "Unknown";
        case DEBUG:
            return "Debug";
        case INFO:
            return "Info";
        case ERR:
            return "Error";
    }
}

#ifdef _ANDROID
android_LogPriority logger_level_to_android_level(LoggerLevel level) {
    switch (level) {
    default:
    case UNKNOWN: return ANDROID_LOG_UNKNOWN;
    case DEBUG: return ANDROID_LOG_DEBUG;
    case INFO: return ANDROID_LOG_INFO;
    case ERR: return ANDROID_LOG_ERROR;
    }
}
#endif

void CLogger::log(LoggerLevel level, std::string_view tmp, va_list args) {
#ifdef _ANDROID
    char buffer[1024] = {0};

    vsnprintf(buffer, 1024, tmp.data(), args);
    __android_log_write(logger_level_to_android_level(level), identifier.data(), buffer);
#else
    printf("[%s - %s] ", identifier.data(), logger_level_to_string(level).data());
    vprintf(tmp.data(), args);
    printf("\n");
#endif
}

void CLogger::log(LoggerLevel level, std::string_view tmp, ...) {
    va_list args;
    va_start(args, tmp);
    log(level, tmp, args);
    va_end(args);
}
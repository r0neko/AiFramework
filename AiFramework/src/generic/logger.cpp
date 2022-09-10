#include <generic/logger.hpp>

using namespace ai_framework;

std::string_view logger_level_to_string(LoggerLevel level) {
    switch (level) {
    default:
    case UNKNOWN: return "Unknown";
    case DEBUG: return "Debug";
    case INFO: return "Info";
    case ERR: return "Error";
    }
}

void CLogger::log(LoggerLevel level, std::string_view tmp, va_list args) {
    printf("[%s - %s] ", identifier.data(), logger_level_to_string(level).data());
    vprintf(tmp.data(), args);
    printf("\n");
}

void CLogger::log(LoggerLevel level, std::string_view tmp, ...) {
    va_list args;
    va_start(args, tmp);
    log(level, tmp, args);
    va_end(args);
}
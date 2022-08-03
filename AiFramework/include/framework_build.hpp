#ifndef AI_FRAMEWORK_BUILD_HPP
#define AI_FRAMEWORK_BUILD_HPP

#ifdef _WIN32
#    pragma warning(disable : 4251)
#    define AI_API_IMPORT __declspec(dllimport)
#    define AI_API_EXPORT __declspec(dllexport)
#endif

#ifndef ENGINE_API
#    ifdef _BUILD_AI_FRAMEWORK
#        define AI_API AI_API_EXPORT
#    else
#        define AI_API AI_API_IMPORT
#    endif
#endif

using opaque_t = void *;

#endif
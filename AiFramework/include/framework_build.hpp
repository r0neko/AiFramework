#ifndef AI_FRAMEWORK_BUILD_HPP
#define AI_FRAMEWORK_BUILD_HPP

#ifdef _WIN32
#    pragma warning(disable : 4251)
#    define AI_API_IMPORT __declspec(dllimport)
#    define AI_API_EXPORT __declspec(dllexport)
#else
#    define AI_API_IMPORT
#    define AI_API_EXPORT
#endif

#ifndef AI_API
#    ifdef _BUILD_AI_FRAMEWORK
#        define AI_API AI_API_EXPORT
#    else
#        define AI_API AI_API_IMPORT
#    endif
#endif

#ifndef AI_API_EXTERN
#    ifdef _BUILD_AI_FRAMEWORK
#        define AI_API_EXTERN
#    else
#        define AI_API_EXTERN extern
#    endif
#endif

using opaque_t = void *;

#ifdef _LINUX && _X11
using gfx_opaque_t = long unsigned int;
#define GFX_OPAQUE_NULL 0
#else
using gfx_opaque_t = opaque_t;
#define GFX_OPAQUE_NULL nullptr
#endif

#endif
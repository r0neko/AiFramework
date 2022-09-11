#ifndef WIN32_WGL_EXT_HPP
#define WIN32_WGL_EXT_HPP

// dirty hack to prevent errors
#define WGL_ARB_pbuffer
#define WGL_ARB_render_texture
#define WGL_NV_video_output
#define WGL_EXT_pbuffer
#define WGL_NV_gpu_affinity
#define WGL_NV_video_capture
#define WGL_NV_present_video

#include <Windows.h>

#include <glad/glad_wgl.h>
#include <gl/wglext.h>

#endif
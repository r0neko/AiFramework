#define _LINUX
#define _X11

#ifdef _LINUX
#ifdef _X11
#    include <framework/app_window.hpp>
#    include <framework/error_manager.hpp>
#    include <input/input_manager.hpp>
#    include <glad/glad.h>
#    include <X11/X.h>
#    include <X11/Xlib.h>
#    include <GL/glx.h>

using namespace ai_framework::framework;
using namespace ai_framework::input;

bool AppWindow::init() {
    GLint                   glx_attr[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    XSetWindowAttributes    x_swa{0};

    display_handle = XOpenDisplay(0);

    if (display_handle == nullptr)
    {
        printf("ERROR: Cannot connect to X Server!\n");
        return false;
    }

    auto root = DefaultRootWindow((Display*) display_handle);
    auto glx_vi = glXChooseVisual((Display*) display_handle, 0, glx_attr);

    if(glx_vi == NULL) {
        printf("no appropriate glx_visual found\n\n");
        return false;
    } 
    else {
        printf("glx_visual %p selected\n", (void *)glx_vi->visualid);
    }

    auto color_map = XCreateColormap((Display*) display_handle, root, glx_vi->visual, 0);

    x_swa.colormap = color_map;
    x_swa.event_mask = ExposureMask | KeyPressMask;

    window_handle = (opaque_t) XCreateWindow((Display*) display_handle, root, 0, 0, size.x, size.y, 0, glx_vi->depth, 1, glx_vi->visual, CWColormap | CWEventMask, &x_swa);

    XStoreName((Display*) display_handle, (Window) window_handle, title.c_str());

    if (!renderer.init(display_handle, glx_vi, window_handle, size))
        return false;

    return true;
}

void AppWindow::show() {
    XMapWindow((Display*) display_handle, (Window) window_handle);
}

void AppWindow::destroy() {
    if (is_init()) {
        renderer.destroy();

        XDestroyWindow((Display*) display_handle, (Window) window_handle);

        window_handle = nullptr;
    }
}

void AppWindow::process_events() {
    XEvent xev;
    XNextEvent((Display*) display_handle, &xev);
}

void AppWindow::set_title(std::string_view new_title) {
    XStoreName((Display*) display_handle, (Window) window_handle, new_title.data());
    title = new_title;
}

#endif
#endif
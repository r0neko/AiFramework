#ifdef _LINUX
#    ifdef _X11
#        include <framework/error_manager.hpp>
#        include <input/input_manager.hpp>
#        include <platform/linux/x11/glx_app_window.hpp>
#        include <platform/linux/x11/glx_renderer.hpp>
#        include <platform/platform.hpp>

using namespace ai_framework;
using namespace framework;
using namespace input;
using namespace platform::linux::graphics;

KeyType x_keycode_to_ai_keytype(unsigned int key);
ButtonState x_button_to_ai_buttontype(unsigned int button);

bool GLXAppWindow::init() {
    if (is_init()) {
        ErrorManager::instance().set_error(ErrorType::INIT_FAILURE, "The window is already initialised!");
        return false;
    }

    // reset state
    quit_queued = false;

    // clear errors
    ErrorManager::instance().clear_error();

    GLint glx_attr[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None};
    XSetWindowAttributes win_attr{0};

    XInitThreads();

    // first try to open a connection to the display
    display = XOpenDisplay(0);

    if (display == nullptr) {
        printf("ERROR: Cannot connect to X Server!");
        return false;
    }

    auto root = DefaultRootWindow(display);
    auto glx_vi = glXChooseVisual(display, 0, glx_attr);

    if (glx_vi == NULL) {
        printf("no appropriate glx_visual found\n");
        return false;
    }

    // create a color map
    auto color_map = XCreateColormap(display, root, glx_vi->visual, 0);

    // set win attributes
    win_attr.colormap = color_map;
    win_attr.event_mask = ExposureMask | KeyPressMask;

    window = XCreateWindow(display, root, 0, 0, size.x, size.y, 0, glx_vi->depth, InputOutput, glx_vi->visual, CWColormap | CWEventMask, &win_attr);

    renderer = platform::make_renderer();

    GLXRendererContext ctx{display, window, glx_vi};

    if (!renderer->init(&ctx, size))
        return false;

    return true;
}

void GLXAppWindow::show() {
    // make sure we receive input-related events!
    XSelectInput(display, window, KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask);

    XMapWindow(display, window);
    XStoreName(display, window, title.c_str());

    if (!input_thread.joinable()) {
        input_thread = std::thread{[&]() {
            XEvent ev;

            while (!is_quit_queued()) {
                XLockDisplay(display);
                if (XCheckWindowEvent(display, window, KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask, &ev)) {
                    switch (ev.type) {
                    default:
                        break;
                    case MotionNotify:
                        input_manager.update_position({ev.xmotion.x, ev.xmotion.y});
                        break;
                    case ButtonPress:
                    case ButtonRelease:
                        input_manager.update_button_state(x_button_to_ai_buttontype(ev.xbutton.button), ev.type == ButtonPress);
                        break;
                    case KeyPress:
                    case KeyRelease:
                        input_manager.update_key_state(x_keycode_to_ai_keytype(XLookupKeysym(&ev.xkey, 0)), ev.type == KeyPress);
                        break;
                    case Expose:
                        XWindowAttributes xwa;
                        XGetWindowAttributes(display, window, &xwa);
                        renderer->resize(size = {xwa.width, xwa.height});
                        break;
                    }
                }
                XUnlockDisplay(display);
            }
        }};

        input_thread.detach();
    }
}

void GLXAppWindow::destroy() {
    if (is_init()) {
        quit_queued = true;

        renderer->destroy();

        if (input_thread.joinable())
            input_thread.join();

        XDestroyWindow(display, window);
        XCloseDisplay(display);

        renderer = nullptr;
        window = 0;
    }
}

void GLXAppWindow::process_events() {
    // XEvent ev;

    // if (XCheckWindowEvent(display, window, KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask, &ev)) {
    //     switch (ev.type) {
    //     default:
    //         break;
    //     case MotionNotify:
    //         input_manager.update_position({ev.xmotion.x, ev.xmotion.y});
    //         break;
    //     case ButtonPress:
    //     case ButtonRelease:
    //         input_manager.update_button_state(x_button_to_ai_buttontype(ev.xbutton.button), ev.type == ButtonPress);
    //         break;
    //     case KeyPress:
    //     case KeyRelease:
    //         input_manager.update_key_state(x_keycode_to_ai_keytype(XLookupKeysym(&ev.xkey, 0)), ev.type == KeyPress);
    //         break;
    //     case Expose:
    //         XWindowAttributes xwa;
    //         XGetWindowAttributes(display, window, &xwa);
    //         renderer->resize(size = {xwa.width, xwa.height});
    //         break;
    //     }
    // }
}

void GLXAppWindow::set_title(std::string_view new_title) {
    XStoreName(display, window, new_title.data());
    title = new_title;
}

bool GLXAppWindow::is_init() {
    return display != nullptr;
}

// let the fun begin!
KeyType x_keycode_to_ai_keytype(unsigned int key) {
    if (key >= XK_0 && key <= XK_9)
        return (KeyType) (KeyType::KEY_0 + (key - XK_0));
    else if (key >= XK_A && key <= XK_Z)
        return (KeyType) (KeyType::KEY_A + (key - XK_A));
    else if (key >= XK_a && key <= XK_z)
        return (KeyType) (KeyType::KEY_A + (key - XK_a));

    return KeyType::UNKNOWN;
}

ButtonState x_button_to_ai_buttontype(unsigned int button) {
    switch (button) {
    default: break;
    case 1:
        return ButtonState::MOUSE_LEFT;
    case 2:
        return ButtonState::MOUSE_MIDDLE;
    case 3:
        return ButtonState::MOUSE_RIGHT;
    }

    return ButtonState::NONE;
}

#    endif
#endif
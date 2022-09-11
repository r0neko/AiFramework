#ifdef _WINDOWS
#    include <Windows.h>

#    include <framework/error_manager.hpp>
#    include <input/input_manager.hpp>
#    include <platform/platform.hpp>
#    include <platform/windows/wgl/wgl_app_window.hpp>

using namespace ai_framework;
using namespace ai_framework::framework;
using namespace ai_framework::input;

using namespace platform::windows::graphics;

LRESULT __stdcall app_window_static_wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    WGLAppWindow *itx_window = reinterpret_cast<WGLAppWindow *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    if (itx_window) {
        switch (message) {
        case WM_SIZE:
            itx_window->resize({LOWORD(lParam), HIWORD(lParam)});
            break;
        case WM_DESTROY:
        case WM_CLOSE:
            PostQuitMessage(0);
            break;
        case WM_KEYDOWN:
            itx_window->input_manager.update_key_state((KeyType) wParam, true);
            break;
        case WM_KEYUP:
            itx_window->input_manager.update_key_state((KeyType) wParam, false);
            break;
        case WM_MOUSEMOVE:
            itx_window->input_manager.update_position({LOWORD(lParam), HIWORD(lParam)});
            break;
        case WM_LBUTTONDOWN:
            itx_window->input_manager.update_button_state(ButtonState::MOUSE_LEFT, true);
            break;
        case WM_LBUTTONUP:
            itx_window->input_manager.update_button_state(ButtonState::MOUSE_LEFT, false);
            break;
        case WM_MBUTTONDOWN:
            itx_window->input_manager.update_button_state(ButtonState::MOUSE_MIDDLE, true);
            break;
        case WM_MBUTTONUP:
            itx_window->input_manager.update_button_state(ButtonState::MOUSE_MIDDLE, false);
            break;
        case WM_RBUTTONDOWN:
            itx_window->input_manager.update_button_state(ButtonState::MOUSE_RIGHT, true);
            break;
        case WM_RBUTTONUP:
            itx_window->input_manager.update_button_state(ButtonState::MOUSE_RIGHT, false);
            break;
        default: return DefWindowProcA(hWnd, message, wParam, lParam);
        }
        return 0;
    }

    return DefWindowProcA(hWnd, message, wParam, lParam);
}

bool WGLAppWindow::init() {
    if (is_init()) {
        ErrorManager::instance().set_error(ErrorType::INIT_FAILURE, "The window is alread initialised!");
        return false;
    }

    // reset state
    quit_queued = false;

    // clear errors
    ErrorManager::instance().clear_error();

    WNDCLASSEXA wcex{};

    // register window class
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wcex.lpfnWndProc = app_window_static_wndproc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(NULL);
    /*wcex.hIcon = LoadIconW(hInstance, MAKEINTRESOURCE(IDI_LOADER));*/
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = win_class.c_str();
    wcex.hIconSm = wcex.hIcon;

    if (!RegisterClassExA(&wcex)) {
        ErrorManager::instance().set_error(ErrorType::INIT_FAILURE, "Failed to register the window class!");
        return false;
    }

    // create window and center it to the screen
    RECT rect;

    GetClientRect(GetDesktopWindow(), &rect);
    rect.left = (rect.right / 2) - (size.x / 2);
    rect.top = (rect.bottom / 2) - (size.y / 2);

    window_handle = CreateWindowExA(
        WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
        win_class.c_str(),
        title.c_str(),
        WS_OVERLAPPEDWINDOW,
        rect.left,
        rect.top,
        size.x,
        size.y,
        nullptr,
        nullptr,
        GetModuleHandle(NULL),
        nullptr);

    if (!window_handle) {
        ErrorManager::instance().set_error(ErrorType::INIT_FAILURE, "Failed to create the window!");
        return false;
    }

    SetWindowLongPtrW((HWND) window_handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    renderer = platform::make_renderer();

    if (!renderer->init(GetDC((HWND) window_handle), size))
        return false;

    return true;
}

void WGLAppWindow::show() {
    ShowWindow((HWND) window_handle, true);
    UpdateWindow((HWND) window_handle);
}

void WGLAppWindow::destroy() {
    if (is_init()) {
        renderer->destroy();
        renderer = nullptr;

        CloseWindow((HWND) window_handle);
        UnregisterClassA(win_class.data(), GetModuleHandle(NULL));

        window_handle = nullptr;
    }
}

void WGLAppWindow::process_events() {
    MSG msg;

    if (!is_init())
        return;

    if (PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_QUIT)
            quit_queued = true;
    }
}

void WGLAppWindow::set_title(std::string_view new_title) {
    if (is_init())
        SetWindowTextA((HWND) window_handle, new_title.data());

    title = new_title;
}

bool WGLAppWindow::is_init() {
    return window_handle != nullptr;
}

#endif
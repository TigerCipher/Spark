// ------------------------------------------------------------------------------
//
// Spark
//    Copyright 2022 Matthew Rogers
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
// File Name: PlatformWindows.h
// Date File Created: 9/11/2022
// Author: Matt
//
// ------------------------------------------------------------------------------

#ifndef SPARK_PLATFORMWINDOWS_C
#define SPARK_PLATFORMWINDOWS_C

#include "Platform.h"

#if SPLATFORM_WINDOWS

    #include "Spark/Core/Logger.h"

    #include <windows.h>
    #include <windowsx.h>
    #include <stdlib.h>

typedef struct internal_state_
{
    HINSTANCE hinst;
    HWND      hwnd;
} internal_state;

static f64           clock_frequency;
static LARGE_INTEGER start_time;
LRESULT CALLBACK     win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);

b8 platform_startup(platform_state* plat_state, const char* app_name, s32 x, s32 y, s32 width, s32 height)
{
    plat_state->internal_state = malloc(sizeof(internal_state));
    internal_state* state      = (internal_state*) plat_state->internal_state;

    state->hinst   = GetModuleHandleA(0);
    HICON     icon = LoadIcon(state->hinst, IDI_APPLICATION);
    WNDCLASSA wc;
    memset(&wc, 0, sizeof(wc));
    wc.style         = CS_DBLCLKS;
    wc.lpfnWndProc   = win32_process_message;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = state->hinst;
    wc.hIcon         = icon;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL; // NULL for transparent
    wc.lpszClassName = "spark_window_class";

    if (!RegisterClassA(&wc))
    {
        // TODO: If we use this a lot, might be good to make a platform abstracted message box?
        MessageBoxA(0, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
        return FALSE;
    }

    s32 client_x      = x;
    s32 client_y      = y;
    s32 client_width  = width;
    s32 client_height = height;

    s32 window_x      = client_x;
    s32 window_y      = client_y;
    s32 window_width  = client_width;
    s32 window_height = client_height;

    u32 window_style    = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
    u32 window_ex_style = WS_EX_APPWINDOW;

    window_style |= WS_MAXIMIZEBOX;
    window_style |= WS_MINIMIZEBOX;
    window_style |= WS_THICKFRAME;

    RECT border_rect = { 0, 0, 0, 0 };
    AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);

    window_x += border_rect.left;
    window_y += border_rect.top;

    window_width += border_rect.right - border_rect.left;
    window_height += border_rect.bottom - border_rect.top;

    HWND handle = CreateWindowExA(window_ex_style, "spark_window_class", app_name, window_style, window_x, window_y,
                                  window_width, window_height, 0, 0, state->hinst, 0);

    if (handle == 0)
    {
        MessageBoxA(NULL, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);

        SFATAL("Window creation failed!");
        return FALSE;
    } else
    {
        state->hwnd = handle;
    }

    b32 should_activate           = 1; // TODO: false for a window with no input
    s32 show_window_command_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;
    // minimized, use SW_MINIMIZE : SW_SHOWMINNOACTIVE;
    // maximized, use SW_SHOWMAXIMIZED : SW_MAXIMIZE
    ShowWindow(state->hwnd, show_window_command_flags);

    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    clock_frequency = 1.0 / (f64) frequency.QuadPart;
    QueryPerformanceCounter(&start_time);

    return TRUE;
}

void platform_shutdown(platform_state* plat_state)
{
    internal_state* state = (internal_state*) plat_state->internal_state;
    if (state->hwnd)
    {
        DestroyWindow(state->hwnd);
        state->hwnd = 0;
    }
}

b8 platform_pump_messages(platform_state* plat_state)
{
    MSG message;
    while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&message);
        DispatchMessageA(&message);
    }

    return TRUE;
}

void* platform_allocate(u64 size, b8 aligned) { return malloc(size); }
void  platform_free(void* block, b8 aligned) { free(block); }

void* platform_zero_memory(void* block, u64 size) { return memset(block, 0, size); }
void* platform_copy_memory(void* dest, const void* src, u64 size) { return memcpy(dest, src, size); }
void* platform_set_memory(void* dest, s32 value, u64 size) { return memset(dest, value, size); }

void platform_console_write(const char* message, u8 color)
{
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // trace, debug, info, warn, error, fatal
    static u8 levels [ 6 ] = { 8, 1, 2, 6, 4, 64 };
    SetConsoleTextAttribute(console_handle, levels [ color ]);

    OutputDebugStringA(message);
    u64     len         = strlen(message);
    LPDWORD num_written = 0;
    WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD) len, num_written, 0);
}
void platform_console_write_error(const char* message, u8 color)
{
    HANDLE console_handle = GetStdHandle(STD_ERROR_HANDLE);

    // trace, debug, info, warn, error, fatal
    static u8 levels [ 6 ] = { 8, 1, 2, 6, 4, 64 };
    SetConsoleTextAttribute(console_handle, levels [ color ]);

    OutputDebugStringA(message);
    u64     len         = strlen(message);
    LPDWORD num_written = 0;
    WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD) len, num_written, 0);
}

f64 platform_get_time()
{
    LARGE_INTEGER now_time;
    QueryPerformanceCounter(&now_time);
    return (f64) now_time.QuadPart * clock_frequency;
}

void platform_sleep(u64 milliseconds) { Sleep(milliseconds); }

LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM wparam, LPARAM lparam) {
    switch(msg)
    {
    case WM_ERASEBKGND: return 1;
    case WM_CLOSE:
        // TODO Close event
        STRACE("WM_CLOSE");
        return 0;
    case WM_DESTROY:
        STRACE("WM_DESTROY");
        PostQuitMessage(0);
        return 0;
    case WM_SIZE:
    {
//        RECT r;
//        GetClientRect(hwnd, &r);
//        s32 w = r.right - r.left;
//        s32 h = r.bottom - r.top;

        // Resize event
    }break;
    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYUP:
    {
        //        b8 pressed = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
    }break;
    case WM_MOUSEMOVE:{
//        s32 x = GET_X_LPARAM(lparam);
//        s32 y = GET_Y_LPARAM(lparam);

    }break;
    case WM_MOUSEWHEEL:
    {
//        s32 z_delta = GET_WHEEL_DELTA_WPARAM(wparam);
//        if(z_delta != 0)
//        {
//            z_delta = (z_delta < 0) ? -1 : 1;
//        }
    }break;
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
    {
        //        b8 pressed = (msg == WM_LBUTTONDOWN || msg == WM_MBUTTONDOWN || msg == WM_RBUTTONDOWN);
    }break;

    default: break;
    }

    return DefWindowProcA(hwnd, msg, wparam, lparam);

}

#endif


#endif //SPARK_PLATFORMWINDOWS_C

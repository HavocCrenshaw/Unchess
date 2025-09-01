#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include "../include/app.h"

App::App() {
    // Init here
}

LRESULT CALLBACK WindowProcedure(HWND windowHandle, UINT msg, WPARAM basicParams, LPARAM extraParams) {
    switch (msg) {

    case WM_ERASEBKGND: {
        return 1; // We will handle all drawing in WM_PAINT
    }

    case WM_PAINT: {
        PAINTSTRUCT paintInfo = { 0 };
        HDC deviceContextHandle = BeginPaint(windowHandle, &paintInfo);
        if (deviceContextHandle == nullptr) {
            return 0; // Not an error, necessarily. We just have no place to paint.
        }

        FillRect(deviceContextHandle, &paintInfo.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(windowHandle, &paintInfo);
        return 0;
    }

    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0;
    }

    }

    return DefWindowProc(windowHandle, msg, basicParams, extraParams);
}

void App::Create(const WCHAR* windowTitle, int xPos, int yPos, int width, int height, int windowPresentation) {
    constexpr WCHAR CLASS_NAME[] = L"WindowClass";

    HINSTANCE systemResources = nullptr;
    WCHAR* currentInstance = nullptr;

    int defaultWidth, defaultHeight = 0;
    UINT flags = LR_DEFAULTSIZE | LR_SHARED;

    HICON iconHandle = static_cast<HICON>(LoadImageW(systemResources, IDI_APPLICATION, IMAGE_ICON, defaultWidth, defaultHeight, flags));
    if (iconHandle == nullptr) {
        // Error handling
    }

    HCURSOR cursorHandle = static_cast<HCURSOR>(LoadImageW(systemResources, IDC_ARROW, IMAGE_CURSOR, defaultWidth, defaultHeight, flags));
    if (cursorHandle == nullptr) {
        // Error handling
    }

    WNDCLASSEXW windowClass = { 0 };
    windowClass.cbSize = sizeof(WNDCLASSEXW);
    windowClass.style = CS_VREDRAW | CS_HREDRAW;
    windowClass.lpfnWndProc = WindowProcedure;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = GetModuleHandleW(currentInstance);
    windowClass.hIcon = iconHandle;
    windowClass.hCursor = cursorHandle;
    windowClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
    windowClass.lpszMenuName = nullptr;
    windowClass.lpszClassName = CLASS_NAME;
    windowClass.hIconSm = iconHandle;

    if (RegisterClassExW(&windowClass) == 0) {
        // Error handling
    }

    DWORD exStyle = 0;
    DWORD style = WS_OVERLAPPEDWINDOW;
    HWND parentWindow = nullptr;
    HMENU menu = nullptr;
    LPVOID creationParams = nullptr;

    HWND windowHandle = CreateWindowExW(exStyle, CLASS_NAME, windowTitle, style, xPos, yPos, width, height, parentWindow, menu,
            GetModuleHandleW(currentInstance), creationParams);
    if (windowHandle == nullptr) {
        // Error handling
    }

    ShowWindow(windowHandle, windowPresentation);
    UpdateWindow(windowHandle);
}

int App::Run() {
    bool running = true;

    HWND currentWindow = nullptr;
    UINT filterMin = 0;
    UINT filterMax = 0;
    UINT handling = PM_REMOVE;

    MSG msg = { 0 };
    while (running) {
        while (PeekMessageW(&msg, currentWindow, filterMin, filterMax, handling)) {
            if (msg.message == WM_QUIT) {
                running = false;
                break;
            }

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        // Game code.
        
        // We've done what we want, let's pause execution.
        BOOL success = WaitMessage();
        if (!success) {
            // Error handling
        }
    }

    return (int)msg.wParam;
}

void App::Quit() {
    // Deinit here
}

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include "../include/app.h"

int WINAPI wWinMain(_In_ HINSTANCE appHandle, _In_opt_ HINSTANCE /* Unused */, _In_ PWSTR commandLine, _In_ int windowPresentation) {
    App app;

    constexpr WCHAR WINDOW_TITLE[] = L"Unchess";
    int xPos = CW_USEDEFAULT;
    int yPos = CW_USEDEFAULT;
    int width = CW_USEDEFAULT;
    int height = CW_USEDEFAULT;
    
    app.Create(WINDOW_TITLE, xPos, yPos, width, height, windowPresentation);
    int exitCode = app.Run();
    app.Quit();

    return exitCode;
}

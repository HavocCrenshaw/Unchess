#ifndef APP_H
#define APP_H

#include <windows.h>

class App {
public:
    App();

public:
    void Create(const WCHAR* windowTitle, int xPos, int yPos, int width, int height, int windowPresentation);
    int Run();
    void Quit();
};

#endif // APP_H

#pragma once
#include <Buffer.h>

class Window {
public:
    Window(const wchar_t* windowName, const int& m_winWidth, const int& m_winHeight);
    ~Window();

    HDC hdc = NULL;    //检索指定窗口或整个屏幕的工作区的设备上下文的句柄
    HDC screenHDC = NULL;
    int winWidth;
    int winHeight;
private:
    WNDCLASSEX wndClsEx;   //创建一个窗体类
    HWND hwnd = NULL;  //创建一个窗口
};
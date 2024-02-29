#pragma once
#include <Buffer.h>

class Window {
public:
    Window(const wchar_t* windowName, const int& m_winWidth, const int& m_winHeight);
    ~Window();

    HDC hdc = NULL;    //����ָ�����ڻ�������Ļ�Ĺ��������豸�����ĵľ��
    HDC screenHDC = NULL;
    int winWidth;
    int winHeight;
private:
    WNDCLASSEX wndClsEx;   //����һ��������
    HWND hwnd = NULL;  //����һ������
};
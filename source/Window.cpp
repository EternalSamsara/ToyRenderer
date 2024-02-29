#include "Window.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // 特殊消息处理
    switch (uMsg)
    {
    case WM_CLOSE:  // 关闭窗口消息
        if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hwnd);
        }
        break;
    case WM_DESTROY:  // 发出WM_QUIT消息，结束消息循环
        PostQuitMessage(0);
        break;
    default:  // 默认消息处理
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

Window::Window(const wchar_t* windowName, const int& m_winWidth, const int& m_winHeight) :
    winWidth(m_winWidth), winHeight(m_winHeight) {
    wndClsEx = {};
    wndClsEx.cbSize = sizeof(WNDCLASSEX);  //WNDCLASSEX结构所占的字节数
    wndClsEx.style = CS_HREDRAW | CS_VREDRAW;  //类样式。参数是若修改窗口的高度或宽度则重绘整个窗口
    wndClsEx.lpfnWndProc = WindowProc;  //设置窗体的回调函数
    wndClsEx.cbClsExtra = 0;  //类的额外内存，默认为0即可
    wndClsEx.cbWndExtra = 0;  //窗口的额外内存，默认为0即可
    wndClsEx.hInstance = GetModuleHandle(NULL);  //设置窗体所属的应用程序实例
    wndClsEx.hIcon = LoadIcon(NULL, IDI_ERROR);  //设置窗体左上角的图标
    wndClsEx.hCursor = LoadCursor(NULL, IDC_CROSS);  //设置光标
    wndClsEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //获取画刷句柄（将返回的HGDIOBJ进行强制类型转换）
    wndClsEx.lpszMenuName = NULL;  //设置窗体的菜单,没有，填NULL
    wndClsEx.lpszClassName = windowName;  //设置窗体的类名

    //向操作系统注册窗体
    if (!RegisterClassEx(&wndClsEx)) {
        std::cout << "注册窗体失败，错误码：" << GetLastError() << std::endl;
        return;
    }

    hwnd = CreateWindowEx(
        WS_EX_WINDOWEDGE,     // 扩展窗口样式
        windowName,           // 窗口文本
        windowName,           // 窗口文本
        WS_VISIBLE,           // 窗口样式
        CW_USEDEFAULT,        // 窗口左上角x的位置
        CW_USEDEFAULT,        // 窗口左上角y的位置
        CW_USEDEFAULT,        // 窗口的宽度
        CW_USEDEFAULT,        // 窗口的高度
        NULL,                 // 父窗口 
        NULL,                 // 菜单栏
        wndClsEx.hInstance,   // 实例句柄
        NULL                  // ？？？
    );

    if (hwnd == NULL) {
        std::cout << "创建窗体失败" << std::endl;
        return;
    }

    // 检索指定窗口或整个屏幕的工作区的设备上下文的句柄
    hdc = GetDC(hwnd);
    screenHDC = CreateCompatibleDC(hdc);

    // 构建位图信息
    BITMAPINFO bitmapInfo{};
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = winWidth;
    bitmapInfo.bmiHeader.biHeight = winHeight;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;         // four 8-bit components
    bitmapInfo.bmiHeader.biCompression = BI_RGB;
    bitmapInfo.bmiHeader.biSizeImage = winWidth * winHeight * 4;
    // 创建接收指向DIB位值位置的指针
    LPVOID ptr;
    // 创建应用程序可以直接写入的、与设备无关的位图
    HBITMAP hBitmap = CreateDIBSection(hdc, &bitmapInfo, DIB_RGB_COLORS, &ptr, 0, 0);
    if (!hBitmap)
        return;
    HBITMAP screenObject = (HBITMAP)SelectObject(hdc, hBitmap);
    SetWindowPos(hwnd, NULL, 50, 50, winWidth, winHeight, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));

    // 显示窗口
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
}

Window::~Window() {
    DeleteDC(screenHDC);
}
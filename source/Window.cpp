#include "Window.h"


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // ������Ϣ����
    switch (uMsg)
    {
    case WM_CLOSE:  // �رմ�����Ϣ
        if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(hwnd);
        }
        break;
    case WM_DESTROY:  // ����WM_QUIT��Ϣ��������Ϣѭ��
        PostQuitMessage(0);
        break;
    default:  // Ĭ����Ϣ����
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

Window::Window(const wchar_t* windowName, const int& m_winWidth, const int& m_winHeight) :
    winWidth(m_winWidth), winHeight(m_winHeight) {
    wndClsEx = {};
    wndClsEx.cbSize = sizeof(WNDCLASSEX);  //WNDCLASSEX�ṹ��ռ���ֽ���
    wndClsEx.style = CS_HREDRAW | CS_VREDRAW;  //����ʽ�����������޸Ĵ��ڵĸ߶Ȼ������ػ���������
    wndClsEx.lpfnWndProc = WindowProc;  //���ô���Ļص�����
    wndClsEx.cbClsExtra = 0;  //��Ķ����ڴ棬Ĭ��Ϊ0����
    wndClsEx.cbWndExtra = 0;  //���ڵĶ����ڴ棬Ĭ��Ϊ0����
    wndClsEx.hInstance = GetModuleHandle(NULL);  //���ô���������Ӧ�ó���ʵ��
    wndClsEx.hIcon = LoadIcon(NULL, IDI_ERROR);  //���ô������Ͻǵ�ͼ��
    wndClsEx.hCursor = LoadCursor(NULL, IDC_CROSS);  //���ù��
    wndClsEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //��ȡ��ˢ����������ص�HGDIOBJ����ǿ������ת����
    wndClsEx.lpszMenuName = NULL;  //���ô���Ĳ˵�,û�У���NULL
    wndClsEx.lpszClassName = windowName;  //���ô��������

    //�����ϵͳע�ᴰ��
    if (!RegisterClassEx(&wndClsEx)) {
        std::cout << "ע�ᴰ��ʧ�ܣ������룺" << GetLastError() << std::endl;
        return;
    }

    hwnd = CreateWindowEx(
        WS_EX_WINDOWEDGE,     // ��չ������ʽ
        windowName,           // �����ı�
        windowName,           // �����ı�
        WS_VISIBLE,           // ������ʽ
        CW_USEDEFAULT,        // �������Ͻ�x��λ��
        CW_USEDEFAULT,        // �������Ͻ�y��λ��
        CW_USEDEFAULT,        // ���ڵĿ��
        CW_USEDEFAULT,        // ���ڵĸ߶�
        NULL,                 // ������ 
        NULL,                 // �˵���
        wndClsEx.hInstance,   // ʵ�����
        NULL                  // ������
    );

    if (hwnd == NULL) {
        std::cout << "��������ʧ��" << std::endl;
        return;
    }

    // ����ָ�����ڻ�������Ļ�Ĺ��������豸�����ĵľ��
    hdc = GetDC(hwnd);
    screenHDC = CreateCompatibleDC(hdc);

    // ����λͼ��Ϣ
    BITMAPINFO bitmapInfo{};
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = winWidth;
    bitmapInfo.bmiHeader.biHeight = winHeight;
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 32;         // four 8-bit components
    bitmapInfo.bmiHeader.biCompression = BI_RGB;
    bitmapInfo.bmiHeader.biSizeImage = winWidth * winHeight * 4;
    // ��������ָ��DIBλֵλ�õ�ָ��
    LPVOID ptr;
    // ����Ӧ�ó������ֱ��д��ġ����豸�޹ص�λͼ
    HBITMAP hBitmap = CreateDIBSection(hdc, &bitmapInfo, DIB_RGB_COLORS, &ptr, 0, 0);
    if (!hBitmap)
        return;
    HBITMAP screenObject = (HBITMAP)SelectObject(hdc, hBitmap);
    SetWindowPos(hwnd, NULL, 50, 50, winWidth, winHeight, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));

    // ��ʾ����
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
}

Window::~Window() {
    DeleteDC(screenHDC);
}
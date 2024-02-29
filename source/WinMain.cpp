#include "Renderer.h"

static constexpr int deviceWidth = 640;
static constexpr int deviceHeight = 480;


void outputImageToScreen(Window& window, RenderBuffer& buffer) {
    HBITMAP hBitmap = CreateBitmap(window.winWidth, window.winHeight, 1, 32, buffer.getBitmap());
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(window.screenHDC, hBitmap);
    BitBlt(window.hdc, 0, 0, window.winWidth, window.winHeight, window.screenHDC, 0, 0, SRCCOPY);
    SelectObject(window.screenHDC, hOldBitmap);
    DeleteObject(hBitmap);
}

void globalDraw(Window& window) {
    HDC deviceHDC = window.screenHDC;

    std::wstring filename = L"Spere";
    // load texture
    Texture texture(1024, 1024);
    getTexture(texture,  L"Spere.png");

    // load model
    Mesh cube;
    cube.importObjModel(filename + L".obj");
    cube.transform.position = { 0.0f, 0.0f, 0.0f };
    cube.texture = texture;

    // set light
    Light light(Color{ 1.0f,1.0f,1.0f,1.0f }, 1.0f);
    light.transform.position = { 5.0f, 5.0f, 5.0f };
    light.dir = { 1.0f,1.0f,1.0f };
    light.transform.getModelMat();
    std::cout << "light modelMat\n" << light.transform.modelMat;

    // set camera
    Camera cam(45.0f);
    cam.transform.position = { 70.0f, 50.0f, 70.0f };
    cam.transform.rotation = { 30.0f, 30.0f, 0.0f };
    cam.transform.getModelMat();
    std::cout << "camera modelMat\n" << cam.transform.modelMat;
        
    //transform.viewMat = cam.View();
    cam.LookAt(cube.transform.position);
    std::cout << "viewMat\n" << cam.viewMat;

    cam.OrthoProjection(deviceWidth, deviceHeight, -1.0f, -100.0f);//Projection(2.0f, -2.0f, -2.0f, 2.0f, -1.0f, -100.0f); //t, b, l, r, n, f
    std::cout << "orthoProjectMat\n" << cam.orthoProjectMat;

    Matrix4f mvp = cam.orthoProjectMat * cam.viewMat * cam.transform.modelMat;
    std::cout << "mvp\n" << mvp;

    cam.Viewport(0, 0, deviceWidth, deviceHeight);
    std::cout << "viewport\n" << cam.viewportMat;

    RenderBuffer renderFrame(deviceWidth, deviceHeight);
    DepthBuffer depthFrame(deviceWidth, deviceHeight);

    Renderer render(deviceHDC, renderFrame, depthFrame);

    FlatShader flatShader;
    //GouraudShader gouraudShader;
    render.drawMesh(cube, light, flatShader, cam);
    outputImageToScreen(window, renderFrame);
}

int main() {
    Window window(L"ToyRenderer", deviceWidth, deviceHeight);
    //RenderSpaceInit(window);
    globalDraw(window);
    // ������Ϣ�б�
    MSG msg{};
    // ������ȡ������Ϣ
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

/* ���ܣ���������Ϣ
 * ����
 * hwnd�����ھ��
 * uMsg����Ϣ
 * wParam��32λ���ض�������Ϣ
 * lParam��32λ���ض�������Ϣ
 */
 /*LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
     // ������Ϣ����
     switch (uMsg)
     {
     case WM_PAINT:  // ���ڻ�����Ϣ
     {
         PAINTSTRUCT ps;
         HDC hdc = BeginPaint(hwnd, &ps);
         // ���л��Ʋ�������BeginPaint��EndPaint֮��Ĵ��������
         FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

         EndPaint(hwnd, &ps);
         break;
     }
     case WM_CLOSE:  // �رմ�����Ϣ
         if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
         {
             DestroyWindow(hwnd);
         }
         break;
     case WM_DESTROY:   //  ����WM_QUIT��Ϣ��������Ϣѭ��
         PostQuitMessage(0);
         break;
     default:
         return DefWindowProc(hwnd, uMsg, wParam, lParam);
     }
     // Ĭ����Ϣ����
     return 0;
 }*/

 /* 
  * hInstance���޷��ų����ͣ����ڱ�ʶһ������ʵ��
  * hPrevInstance����ʾ��ǰʵ����ǰһ��ʵ���ľ������Win32�����£���������ΪNULL
  * lpCmdLine�����ڴ�Ŵ��ݸ�Ӧ�ó���Ĳ���
  * nShowCmd�����ƴ��ڵ���ʾ��ʽ
  */
  /*int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
      const wchar_t CLASS_NAME[] = L"Test Window Class";

      WNDCLASS wndcls{}; //����һ��������
      wndcls.cbClsExtra = 0;  //��Ķ����ڴ棬Ĭ��Ϊ0����
      wndcls.cbWndExtra = 0;  //���ڵĶ����ڴ棬Ĭ��Ϊ0����
      wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //��ȡ��ˢ����������ص�HGDIOBJ����ǿ������ת����
      wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);  //���ù��
      wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);  //���ô������Ͻǵ�ͼ��
      wndcls.hInstance = hInstance;  //���ô���������Ӧ�ó���ʵ��
      wndcls.lpfnWndProc = WindowProc;  //���ô���Ļص���������ʱûд��������ΪNULL�����油��
      wndcls.lpszClassName = CLASS_NAME;  //���ô��������
      wndcls.lpszMenuName = NULL;  //���ô���Ĳ˵�,û�У���NULL
      RegisterClass(&wndcls);  //�����ϵͳע�ᴰ��

      // ��������
      HWND hwnd = CreateWindow(
          CLASS_NAME,                     // ��������
          L"Learn to Program Windows",    // �����ı�
          WS_OVERLAPPEDWINDOW,            // �������
          CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,  // ���ڳߴ��λ��
          NULL,       // ������
          NULL,       // �˵���
          hInstance,  // ʵ�����
          NULL        // ������
      );
      // �����ڶ���Ϊ�����˳�����
      if (hwnd == NULL)
      {
          return 0;
      }

      // ����ָ�����ڻ�������Ļ�Ĺ��������豸�����ĵľ��
      HDC hdc = GetDC(hwnd);
      // ����λͼ��Ϣ
      BITMAPINFO bitmapInfo{};
      bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      bitmapInfo.bmiHeader.biWidth = 640;
      bitmapInfo.bmiHeader.biHeight = 480;
      bitmapInfo.bmiHeader.biPlanes = 1;
      bitmapInfo.bmiHeader.biBitCount = 32;         // four 8-bit components
      bitmapInfo.bmiHeader.biCompression = BI_RGB;
      bitmapInfo.bmiHeader.biSizeImage = 640 * 480 * 4;
      // ��������ָ��DIBλֵλ�õ�ָ��
      LPVOID ptr;
      // ����Ӧ�ó������ֱ��д��ġ����豸�޹ص�λͼ
      HBITMAP hBitmap = CreateDIBSection(hdc, &bitmapInfo, DIB_RGB_COLORS, &ptr, 0, 0);
      if (!hBitmap)
          return 0;
      HBITMAP screenObject = (HBITMAP)SelectObject(hdc, hBitmap);
      SetWindowPos(hwnd, NULL, 50, 50, 640, 480, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));

      // ��ʾ����
      ShowWindow(hwnd, SW_SHOWNORMAL);
      UpdateWindow(hwnd);

      // ������Ϣ�б�
      MSG msg{};
      // ������ȡ������Ϣ
      while (GetMessage(&msg, NULL, 0, 0))
      {
          TranslateMessage(&msg);
          DispatchMessage(&msg);
      }
      return 0;
  }*/
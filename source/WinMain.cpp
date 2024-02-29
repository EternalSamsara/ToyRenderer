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
    // 创建消息列表
    MSG msg{};
    // 持续获取窗口消息
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

/* 功能：处理窗口消息
 * 参数
 * hwnd：窗口句柄
 * uMsg：消息
 * wParam：32位的特定附加信息
 * lParam：32位的特定附加信息
 */
 /*LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
     // 特殊消息处理
     switch (uMsg)
     {
     case WM_PAINT:  // 窗口绘制消息
     {
         PAINTSTRUCT ps;
         HDC hdc = BeginPaint(hwnd, &ps);
         // 所有绘制操作均在BeginPaint和EndPaint之间的代码内完成
         FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

         EndPaint(hwnd, &ps);
         break;
     }
     case WM_CLOSE:  // 关闭窗口消息
         if (MessageBox(hwnd, L"Really quit?", L"My application", MB_OKCANCEL) == IDOK)
         {
             DestroyWindow(hwnd);
         }
         break;
     case WM_DESTROY:   //  发出WM_QUIT消息，结束消息循环
         PostQuitMessage(0);
         break;
     default:
         return DefWindowProc(hwnd, uMsg, wParam, lParam);
     }
     // 默认消息处理
     return 0;
 }*/

 /* 
  * hInstance：无符号长整型，用于标识一个程序实例
  * hPrevInstance：表示当前实例的前一个实例的句柄，在Win32环境下，参数总是为NULL
  * lpCmdLine：用于存放传递给应用程序的参数
  * nShowCmd：控制窗口的显示方式
  */
  /*int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
      const wchar_t CLASS_NAME[] = L"Test Window Class";

      WNDCLASS wndcls{}; //创建一个窗体类
      wndcls.cbClsExtra = 0;  //类的额外内存，默认为0即可
      wndcls.cbWndExtra = 0;  //窗口的额外内存，默认为0即可
      wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //获取画刷句柄（将返回的HGDIOBJ进行强制类型转换）
      wndcls.hCursor = LoadCursor(NULL, IDC_CROSS);  //设置光标
      wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);  //设置窗体左上角的图标
      wndcls.hInstance = hInstance;  //设置窗体所属的应用程序实例
      wndcls.lpfnWndProc = WindowProc;  //设置窗体的回调函数，暂时没写，先设置为NULL，后面补上
      wndcls.lpszClassName = CLASS_NAME;  //设置窗体的类名
      wndcls.lpszMenuName = NULL;  //设置窗体的菜单,没有，填NULL
      RegisterClass(&wndcls);  //向操作系统注册窗体

      // 创建窗口
      HWND hwnd = CreateWindow(
          CLASS_NAME,                     // 窗口名称
          L"Learn to Program Windows",    // 窗口文本
          WS_OVERLAPPEDWINDOW,            // 窗口外观
          CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,  // 窗口尺寸和位置
          NULL,       // 父窗口
          NULL,       // 菜单栏
          hInstance,  // 实例句柄
          NULL        // ？？？
      );
      // 若窗口对象为空则退出程序
      if (hwnd == NULL)
      {
          return 0;
      }

      // 检索指定窗口或整个屏幕的工作区的设备上下文的句柄
      HDC hdc = GetDC(hwnd);
      // 构建位图信息
      BITMAPINFO bitmapInfo{};
      bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
      bitmapInfo.bmiHeader.biWidth = 640;
      bitmapInfo.bmiHeader.biHeight = 480;
      bitmapInfo.bmiHeader.biPlanes = 1;
      bitmapInfo.bmiHeader.biBitCount = 32;         // four 8-bit components
      bitmapInfo.bmiHeader.biCompression = BI_RGB;
      bitmapInfo.bmiHeader.biSizeImage = 640 * 480 * 4;
      // 创建接收指向DIB位值位置的指针
      LPVOID ptr;
      // 创建应用程序可以直接写入的、与设备无关的位图
      HBITMAP hBitmap = CreateDIBSection(hdc, &bitmapInfo, DIB_RGB_COLORS, &ptr, 0, 0);
      if (!hBitmap)
          return 0;
      HBITMAP screenObject = (HBITMAP)SelectObject(hdc, hBitmap);
      SetWindowPos(hwnd, NULL, 50, 50, 640, 480, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));

      // 显示窗口
      ShowWindow(hwnd, SW_SHOWNORMAL);
      UpdateWindow(hwnd);

      // 创建消息列表
      MSG msg{};
      // 持续获取窗口消息
      while (GetMessage(&msg, NULL, 0, 0))
      {
          TranslateMessage(&msg);
          DispatchMessage(&msg);
      }
      return 0;
  }*/
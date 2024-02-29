#include "Texture.h"


Texture::Texture(const unsigned w, const unsigned h):
    width(w), height(h), content(w * h, Color{ 0.0f,0.0f,0.0f,0.0f }) {};

Color Texture::getTextureColor(Vertex2f uv) {
    int x = uv.x * width, y = (1 - uv.y) * height;
    x = x == width ? x - 1 : x;
    y = y == height ? y - 1 : y;
    return content[y * width + x];
}

void getTexture(Texture& texture, const std::wstring& path) {
    Gdiplus::GdiplusStartupInput gdiplusstartupinput;
    ULONG_PTR gdiplustoken;
    Gdiplus::GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, NULL);

    std::ifstream is(rootPath + path, std::ifstream::in | std::ios::binary);
    Gdiplus::Bitmap* img = new Gdiplus::Bitmap((rootPath + path).c_str());
    unsigned height = img->GetHeight();
    unsigned width = img->GetWidth();

    Gdiplus::Color color;
    /*for (unsigned x = 0; x < width; x++)
        for (unsigned y = 0; y < height; y++) {
            img->GetPixel(x, y, &color);
            int r = static_cast<int>(color.GetRed());
            int g = static_cast<int>(color.GetGreen());
            int b = static_cast<int>(color.GetBlue());
            content[x][y].r = r / 255.0f;
            content[x][y].g = g / 255.0f;
            content[x][y].b = b / 255.0f;
        }*/

    for (unsigned y = 0; y < height; y++)
        for (unsigned x = 0; x < width; x++) {
            img->GetPixel(x, y, &color);
            int r = static_cast<int>(color.GetRed());
            int g = static_cast<int>(color.GetGreen());
            int b = static_cast<int>(color.GetBlue());
            int a = static_cast<int>(color.GetAlpha());
            texture.content[y * width + x].r = r / 255.0f;
            texture.content[y * width + x].g = g / 255.0f;
            texture.content[y * width + x].b = b / 255.0f;
            texture.content[y * width + x].a = a / 255.0f;
            /*if (y == 260)
                printf_s("%d, %d, %f, %f, %f\n", x, y, r / 255.0f, g / 255.0f, b / 255.0f);*/
        }

    delete img;
    Gdiplus::GdiplusShutdown(gdiplustoken);
}
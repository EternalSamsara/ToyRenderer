#pragma once
#include "Shader.h"

class DepthBuffer {
public:
	DepthBuffer(const int& m_width, const int& m_height);
	~DepthBuffer();

	float& operator()(const int& row, const int& col);
	float operator()(const int& row, const int& col) const;
	bool ZBuffer(const int& i, const int& j, const float& dp);
private:
	int width;
	int height;
	std::vector<float> DepthImage;
};


class RenderBuffer {
public:
	RenderBuffer(const int& m_width, const int& m_height);
	~RenderBuffer();

	//Color& operator()(const int& row, const int& col);
	//Color operator()(const int& row, const int& col) const;
	BYTE& operator()(const int& row, const int& col, const int& c);
	BYTE operator()(const int& row, const int& col, const int& c) const;
	BYTE* getBitmap();
private:
	int width;
	int height;
	BITMAP image;
	BYTE *bitmapData;
	std::vector<Color> RGBImage;
};


#include "Buffer.h"


DepthBuffer::DepthBuffer(const int& m_width, const int& m_height) : width(m_width), height(m_height) {
	DepthImage = std::vector<float>(width * height, 1.0f);
}

DepthBuffer::~DepthBuffer() {};

float& DepthBuffer::operator()(const int& i, const int& j) {
	return DepthImage[j * width + i];
}

float DepthBuffer::operator()(const int& i, const int& j) const {
	return DepthImage[j * width + i];
}

bool DepthBuffer::ZBuffer(const int& i, const int& j, const float& dp) {
	if (i >= 0 && i < width && j >= 0 && j < height) {
		if (DepthImage[j * width + i] >= dp) {
			DepthImage[j * width + i] = dp;
			return true;
		}
	}
	return false;
}


RenderBuffer::RenderBuffer(const int& m_width, const int& m_height) : width(m_width), height(m_height) {
	RGBImage = std::vector<Color>(width * height, { 255, 255, 255 });
	bitmapData = (BYTE*)malloc(width * height * 4 * sizeof(BYTE));
	std::memset(bitmapData, static_cast<BYTE>(255), width * height * 4);
}
RenderBuffer::~RenderBuffer() {
	//delete[] bitmapData;
}

BYTE& RenderBuffer::operator()(const int& i, const int& j, const int& c) {
	return bitmapData[j * width * 4 + i * 4 + c];
}

BYTE RenderBuffer::operator()(const int& i, const int& j, const int& c) const {
	return bitmapData[j * width * 4 + i * 4 + c];
}

BYTE* RenderBuffer::getBitmap() {
	return bitmapData;
}

/*Color& RenderBuffer::operator()(const int& i, const int& j) {
	return RGBImage[j * width + i];
}

Color RenderBuffer::operator()(const int& i, const int& j) const {
	return RGBImage[j * width + i];
}*/
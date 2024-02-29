#pragma once
#include "Window.h"


class Renderer {
public:
	Renderer(const HDC& m_hdc, const RenderBuffer& m_renderFrame, const DepthBuffer& m_depthFrame);
	~Renderer();

	void drawMesh(Mesh& mesh, Light& light, Shader& shader, const Camera& cam);
	void drawTrianglePrimitive(const SVertex& v1, const SVertex& v2, const SVertex& v3, Shader& shader);
	void drawPixel(const int& x, const int& y, const Color& c);

	Vertex4f Rasterization(const Vertex4f& v, const Matrix4f& viewport);

	// �����߿�ģ��
	void drawWireframe(const std::vector<Vertex4f>& points, const std::vector<std::vector<int>>& face);
	// �������귨����������
	void drawTriangleBarycentricCoordinate(const Vertex3f& v1, const Vertex3f& v2, const Vertex3f& v3);
	// ɨ���߷�����������
	void drawTriangleScanLine(const Vertex3f& v1, const Vertex3f& v2, const Vertex3f& v3);
	// Breshman�����㷨
	void drawLineBreshman(const int& m_x1, const int& m_y1, const int& m_x2, const int& m_y2);
	// ��ֵ΢�ֻ����㷨
	void drawLineDDA(const Vertex3f& v1, const Vertex3f& v2);
private:
	HDC deviceHDC;
	Matrix4f viewportMat;
	RenderBuffer renderFrame;
	DepthBuffer depthFrame;
};
#include "Renderer.h"

Renderer::Renderer(const HDC& m_hdc, const RenderBuffer& m_renderFrame, const DepthBuffer& m_depthFrame) :
	deviceHDC(m_hdc), renderFrame(m_renderFrame), depthFrame(m_depthFrame) {}

Renderer::~Renderer() {}

void Renderer::drawPixel(const int& x, const int& y, const Color& c) {
	SetPixelV(deviceHDC, x, y, RGB(int(255 * c.r), int(255 * c.g), int(255 * c.b)));
}

void Renderer::drawMesh(Mesh& mesh, Light& light, Shader& shader, const Camera& cam) {
	SVertex sVertex[4];
	Vertex4f pix;
	Vertex3f g;
	int count = 0, idx = 0;

	shader.mesh = &mesh;
	shader.meshModelView = cam.viewMat * mesh.transform.modelMat;
	shader.light = &light;
	shader.lightModelView = cam.viewMat * light.transform.modelMat;
	shader.cameraProjection = cam.orthoProjectMat;

	for (int i = 0; i < mesh.perFaceVertexNum.size(); i++) {
		for (int j = 0; j < mesh.perFaceVertexNum[i]; j++) {
			idx = count + j;
			shader.VertexShader(sVertex[j], idx);
			pix = Rasterization(sVertex[j].loc, cam.viewportMat);
			// perspective divide
			sVertex[j].weight = pix.w;
			sVertex[j].screenPix = squeeze<float, 3>(pix / pix.w);
		}
		if (mesh.perFaceVertexNum[i] == 3) {
			drawTrianglePrimitive(sVertex[0], sVertex[1], sVertex[2], shader);
		}
		else if (mesh.perFaceVertexNum[i] == 4) {
			drawTrianglePrimitive(sVertex[0], sVertex[1], sVertex[2], shader);
			drawTrianglePrimitive(sVertex[0], sVertex[2], sVertex[3], shader);
		}
		count += mesh.perFaceVertexNum[i];
	}
}

void Renderer::drawTrianglePrimitive(const SVertex& v0, const SVertex& v1, const SVertex& v2, Shader& shader) {
	int x_min = min(v0.screenPix.x, min(v1.screenPix.x, v2.screenPix.x));
	int y_min = min(v0.screenPix.y, min(v1.screenPix.y, v2.screenPix.y));
	int x_max = max(v0.screenPix.x, max(v1.screenPix.x, v2.screenPix.x));
	int y_max = max(v0.screenPix.y, max(v1.screenPix.y, v2.screenPix.y));

	Color pColor;
	int red = 0, green = 0, blue = 0, alpha = 0;
	for (int pX = x_min; pX <= x_max; pX++) {
		for (int pY = y_min; pY <= y_max; pY++) {
			Vertex3f p = { pX * 1.0f, pY * 1.0f, 0.0f };  // x, y, depth
			Vertex3f g = getBarycentric(v0.screenPix, v1.screenPix, v2.screenPix, p);
			if (g.x < 0 || g.y < 0 || g.z < 0)
				continue;

			// 重心坐标透视矫正插值
			g.x /= v0.weight;
			g.y /= v1.weight;
			g.z /= v2.weight;
			float z_n = g.x + g.y + 2 * g.z;
			g /= z_n;

			// 计算正确的深度值
			p.z = v0.screenPix.z * g.x + v1.screenPix.z * g.y + v2.screenPix.z * g.z;

			// z-buffer
			if (depthFrame.ZBuffer(pX, pY, p.z)) {
				// fragment shader
				if (shader.FragmentShader(pColor, g, v0, v1, v2)) {
					// renderFrame set color
					red = static_cast<int>(pColor.r * 255);
					green = static_cast<int>(pColor.g * 255);
					blue = static_cast<int>(pColor.b * 255);
					alpha = static_cast<int>(pColor.a * 255);
					renderFrame(pX, pY, 0) = static_cast<BYTE>(blue);
					renderFrame(pX, pY, 1) = static_cast<BYTE>(green);
					renderFrame(pX, pY, 2) = static_cast<BYTE>(red);
					renderFrame(pX, pY, 3) = static_cast<BYTE>(alpha);
				}
			}
		}
	}
}

Vertex4f Renderer::Rasterization(const Vertex4f& v, const Matrix4f& viewport) {
	return viewport * v;
}
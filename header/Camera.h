#pragma once

#include "Geometry.h"
#include "Object.h"

class Camera: public Object {
public:
	Camera(const float m_eyeFov);
	~Camera();

	// 计算视图矩阵
	void View();
	// 计算LookAt矩阵
	void LookAt(Vertex3f& target);
	// 计算正交投影矩阵
	void OrthoProjection(float winWidth, float winHeight, float zNear, float zFar);
	// 手动设置投影空间
	Matrix4f Projection(const float& t, const float& b, const float& l, const float& r, const float& n, const float& f);
	// 视角计算投影空间
	Matrix4f Projection(const float& aspectRatio);
	// 计算视口矩阵（NDC到屏幕坐标）
	void Viewport(const int& x, const int& y, const int& w, const int& h);

	float eyeFov;
	Matrix4f viewMat;
	Matrix4f orthoProjectMat;
	Matrix4f perspProjectMat;
	Matrix4f viewportMat;
};
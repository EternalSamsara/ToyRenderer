#pragma once

#include "Geometry.h"
#include "Object.h"

class Camera: public Object {
public:
	Camera(const float m_eyeFov);
	~Camera();

	// ������ͼ����
	void View();
	// ����LookAt����
	void LookAt(Vertex3f& target);
	// ��������ͶӰ����
	void OrthoProjection(float winWidth, float winHeight, float zNear, float zFar);
	// �ֶ�����ͶӰ�ռ�
	Matrix4f Projection(const float& t, const float& b, const float& l, const float& r, const float& n, const float& f);
	// �ӽǼ���ͶӰ�ռ�
	Matrix4f Projection(const float& aspectRatio);
	// �����ӿھ���NDC����Ļ���꣩
	void Viewport(const int& x, const int& y, const int& w, const int& h);

	float eyeFov;
	Matrix4f viewMat;
	Matrix4f orthoProjectMat;
	Matrix4f perspProjectMat;
	Matrix4f viewportMat;
};
#include "Camera.h"

Camera::Camera(const float m_eyeFov) : 
	eyeFov(m_eyeFov), 
	viewMat(Matrix4f::Identity()), 
	orthoProjectMat(Matrix4f::Identity()),
	perspProjectMat(Matrix4f::Identity()),
	viewportMat(Matrix4f::Identity()) {
};

Camera::~Camera() {}

void Camera::View() {
	float xAngleRadian = transform.rotation.x * PI / 180.0f;
	float yAngleRadian = transform.rotation.y * PI / 180.0f;
	float zAngleRadian = transform.rotation.z * PI / 180.0f;

	// Camera inv rotation
	Matrix4f invRotationX = Matrix4f::Identity();
	invRotationX(1, 1) = std::cos(xAngleRadian);  invRotationX(1, 2) = -std::sin(xAngleRadian);
	invRotationX(2, 1) = std::sin(xAngleRadian);  invRotationX(2, 2) = std::cos(xAngleRadian);

	Matrix4f invRotationY = Matrix4f::Identity();
	invRotationY(0, 0) = std::cos(yAngleRadian);   invRotationY(0, 2) = std::sin(yAngleRadian);
	invRotationY(2, 0) = -std::sin(yAngleRadian);  invRotationY(2, 2) = std::cos(yAngleRadian);

	Matrix4f invRotationZ = Matrix4f::Identity();
	invRotationZ(0, 0) = std::cos(zAngleRadian);  invRotationZ(0, 1) = -std::sin(zAngleRadian);
	invRotationZ(1, 0) = std::sin(zAngleRadian);  invRotationZ(1, 1) = std::cos(zAngleRadian);

	Matrix4f invRotationMat = invRotationZ * invRotationY * invRotationX;

	// Camera inv translate
	Matrix4f invTranslateMat = Matrix4f::Identity();
	invTranslateMat(0, 3) = -transform.position.x;
	invTranslateMat(1, 3) = -transform.position.y;
	invTranslateMat(2, 3) = -transform.position.z;
	viewMat = invTranslateMat * invRotationMat;
}

void Camera::Viewport(const int& x, const int& y, const int& w, const int& h) {
	// x，y为窗口的左下角坐标；w，h为窗口的宽高
	viewportMat(0, 0) = w / 2.0;  viewportMat(0, 3) = (w - 1) / 2.0;
	viewportMat(1, 1) = h / 2.0;  viewportMat(1, 3) = (h - 1) / 2.0;
}

void Camera::LookAt(Vertex3f& target) {
	// 计算相机自身在世界坐标系下的下x，y，z轴向量
	Vertex3f vz = (target - transform.position).normalize();
	Vertex3f vx = Vertex3f::cross(up, vz).normalize();
	Vertex3f vy = Vertex3f::cross(vz, vx).normalize();

	Matrix4f vMat = Matrix4f::Identity();
	Matrix4f trMat = Matrix4f::Identity();
	for (int i = 0; i < 3; i++) {
		vMat(0, i) = vx[i];
		vMat(1, i) = vy[i];
		vMat(2, i) = -vz[i];
		trMat(i, 3) = -transform.position[i];
	}
	std::cout << "vMat\n" << vMat;
	std::cout << "trMat\n" << trMat;

	viewMat = vMat * trMat;
}

void Camera::OrthoProjection(float winWidth, float winHeight, float zNear, float zFar) {
	const float ratio = 1024.0f;
	const float widthHeightRatio = winWidth / winHeight;
	const float right = widthHeightRatio * ratio / 2.0f / 50.0f;
	const float left = -right;
	const float top = ratio / 2.0f / 50.0f;
	const float bottom = -top;
	// 缩放
	orthoProjectMat(0, 0) = 2.0f / (right - left);
	orthoProjectMat(1, 1) = 2.0f / (top - bottom);
	orthoProjectMat(2, 2) = 2.0f / (zNear - zFar);
	orthoProjectMat(3, 3) = 1.0f;
	// 平移
	orthoProjectMat(0, 3) = -(right + left) / (right - left);
	orthoProjectMat(1, 3) = -(top + bottom) / (top - bottom);
	orthoProjectMat(2, 3) = -(zNear + zFar) / (zNear - zFar);
	std::cout << "orthoMat\n" << orthoProjectMat;
}

Matrix4f Camera::Projection(const float& t, const float& b, 
							const float& l, const float& r, 
							const float& n, const float& f) {
	// 正交变换
	Matrix4f orthoMat;
	// 缩放
	orthoMat(0, 0) = 2.0f / (r - l);
	orthoMat(1, 1) = 2.0f / (t - b);
	orthoMat(2, 2) = 2.0f / (n - f);
	orthoMat(3, 3) = 1.0f;
	// 平移
	orthoMat(0, 3) = -(r + l) / (r - l);
	orthoMat(1, 3) = -(t + b) / (t - b);
	orthoMat(2, 3) = -(n + f) / (n - f);
	std::cout << "orthoMat\n" << orthoMat;

	// 透视变换
	Matrix4f perspToOrtho;
	perspToOrtho(0, 0) = n;
	perspToOrtho(1, 1) = n;
	perspToOrtho(2, 2) = n + f;
	perspToOrtho(2, 3) = -n * f;
	perspToOrtho(3, 2) = 1;
	std::cout << "perspToOrtho\n" << perspToOrtho;

	Matrix4f perspertiveMat;
	perspertiveMat(0, 0) = 2 * n / (r - l); perspertiveMat(0, 1) = 0;               perspertiveMat(0, 2) = (l + r) / (l - r); perspertiveMat(0, 3) = 0;
	perspertiveMat(1, 0) = 0;               perspertiveMat(1, 1) = 2 * n / (t - b); perspertiveMat(1, 2) = (b + t) / (b - t); perspertiveMat(1, 3) = 0;
	perspertiveMat(2, 0) = 0;               perspertiveMat(2, 1) = 0;               perspertiveMat(2, 2) = (n + f) / (n - f); perspertiveMat(2, 3) = 2 * n * f / (f - n);
	perspertiveMat(3, 0) = 0;               perspertiveMat(3, 1) = 0;               perspertiveMat(3, 2) = 1;                 perspertiveMat(3, 3) = 0;
	std::cout << "perspertiveMat\n" << perspertiveMat;
	return orthoMat; // orthoMat * perspToOrtho;
}

Matrix4f Camera::Projection(const float& aspectRatio) {
	float t = 1.0f;  // std::tan(0.5f * eyeFov * PI / 180);
	float b = -t;
	float r = t;
	float l = -r;
	float n = 1.0f;
	float f = 10.0f;
	//printf_s("%f, %f, %f, %f\n", t, b, r, l);

	// 正交变换
	Matrix4f orthoMat;
	// 缩放
	orthoMat(0, 0) = 2 / (r - l);
	orthoMat(1, 1) = 2 / (t - b);
	orthoMat(2, 2) = 2 / (n - f);
	orthoMat(3, 3) = 1;
	// 平移
	orthoMat(0, 3) = -(r + l) / (r - l);
	orthoMat(1, 3) = -(t + b) / (t - b);
	orthoMat(2, 3) = -(n + f) / (n - f);
	std::cout << "orthoMat\n" << orthoMat;

	// 透视变换
	Matrix4f perspToOrtho;
	perspToOrtho(0, 0) = n;
	perspToOrtho(1, 1) = n;
	perspToOrtho(2, 2) = n + f;
	perspToOrtho(2, 3) = -n * f;
	perspToOrtho(3, 2) = 1;
	std::cout << "perspToOrtho\n" << perspToOrtho;

	Matrix4f perspertiveMat;
	perspertiveMat(0, 0) = 2 * n / (r - l); perspertiveMat(0, 1) = 0;               perspertiveMat(0, 2) = (l + r) / (l - r); perspertiveMat(0, 3) = 0;
	perspertiveMat(1, 0) = 0;               perspertiveMat(1, 1) = 2 * n / (t - b); perspertiveMat(1, 2) = (b + t) / (b - t); perspertiveMat(1, 3) = 0;
	perspertiveMat(2, 0) = 0;               perspertiveMat(2, 1) = 0;               perspertiveMat(2, 2) = (n + f) / (n - f); perspertiveMat(2, 3) = 2 * n * f / (f - n);
	perspertiveMat(3, 0) = 0;               perspertiveMat(3, 1) = 0;               perspertiveMat(3, 2) = 1;                 perspertiveMat(3, 3) = 0;
	std::cout << "perspertiveMat\n" << perspertiveMat;
	return perspertiveMat;  // orthoMat * perspToOrtho
}
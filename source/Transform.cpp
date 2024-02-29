#include "Transform.h"


Transform::Transform() : 
	position({ 0.0f, 0.0f, 0.0f }), rotation({ 0.0f, 0.0f, 0.0f }), scaling({ 1.0f, 1.0f, 1.0f }), 
	modelMat(Matrix4f::Identity()) {};

Transform::~Transform() {}

void Transform::getModelMat() {
	Matrix4f translateMat = Matrix4f::Identity();
	// Translate
	translateMat(0, 3) = position.x;
	translateMat(1, 3) = position.y;
	translateMat(2, 3) = position.z;
	// Rotate
	// Scale
	// Total
	modelMat = translateMat;
}

Transform& Transform::translate(const float xWorldAxisMotion, const float yWorldAxisMotion, const float zWorldAxisMotion) {
	position.x += xWorldAxisMotion;
	position.y += yWorldAxisMotion;
	position.z += zWorldAxisMotion;
	return *this;
}

// 四元数旋转
Transform& Transform::rotate(const float xAngle, const float yAngle, const float zAngle) {
	return *this;
}

// 欧拉角旋转
Transform& Transform::rotateEuler(const float xAngle, const float yAngle, const float zAngle) {
	rotation.x += xAngle;
	rotation.y += yAngle;
	rotation.z += zAngle;
	return *this;
}

Transform& Transform::scale(const float xCoef, const float yCoef, const float zCoef) {
	scaling.x += xCoef;
	scaling.y += yCoef;
	scaling.z += zCoef;
	return *this;
}
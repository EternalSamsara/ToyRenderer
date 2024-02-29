#pragma once

#include "Matrix.h"

class Transform {
public:
	Transform();
	~Transform();

	Transform& translate(const float xWorldAxisMotion, const float yWorldAxisMotion, const float zWorldAxisMotion);
	Transform& rotate(const float xAngle, const float yAngle, const float zAngle);
	Transform& rotateEuler(const float xAngle, const float yAngle, const float zAngle);
	Transform& scale(const float xCoef, const float yCoef, const float zCoef);
	void getModelMat();

	Matrix4f modelMat;
	Vertex3f position;
	Vertex3f rotation;
	Vertex3f scaling;
};
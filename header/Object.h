#pragma once
#include "Transform.h"

class Object {
public:
	Transform transform;

	Vertex3f up = { 0.0f, 1.0f, 0.0f };
	Vertex3f bottom = { 0.0f, -1.0f, 0.0f };
	Vertex3f left = { -1.0f, 0.0f, 0.0f };
	Vertex3f right = { 1.0f, 0.0f, 0.0f };
	Vertex3f forward = { 0.0f, 0.0f, 1.0f };
	Vertex3f back = { 0.0f, 0.0f, -1.0f };
};
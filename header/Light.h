#pragma once
#include "Color.h"
#include "Object.h"

class Light: public Object {
public:
	Light() = default;
	Light(const Color& color, float intensity);
	~Light();

	Vertex3f dir;
	Color color;
	float intensity = 1.0;
};
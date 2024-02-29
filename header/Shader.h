#pragma once

#include "Camera.h"
#include "Texture.h"
#include "Mesh.h"

struct SVertex {
	Vertex4f loc;
	Vertex3f normal;
	Vertex3f screenPix;
	Vertex2f uv;
	Color color;
	float weight;
};

class Shader {
public:
	virtual void VertexShader(SVertex& sVertex, int idx) = 0;
	virtual bool FragmentShader(Color& pColor, const Vertex3f& g,
								const SVertex v0, const SVertex v1, const SVertex v2) = 0;

	Mesh *mesh;
	Light *light;
	Matrix4f meshModelView;
	Matrix4f lightModelView;
	Matrix4f cameraProjection;
};

class FlatShader : public Shader {
public:
	FlatShader();
	~FlatShader();

	virtual void VertexShader(SVertex& sVertex, int idx) override;
	virtual bool FragmentShader(Color& pColor, const Vertex3f& g,
								const SVertex v0, const SVertex v1, const SVertex v2) override;
};

/*class GouraudShader : public Shader {
public:
	GouraudShader();
	~GouraudShader();

	virtual void VertexShader(SVertex& sVertex, int idx) override;
	virtual bool FragmentShader(Color& pColor, const Vertex3f& g,
								const SVertex v0, const SVertex v1, const SVertex v2) override;
};

class PhongShader : public Shader {
public:
	PhongShader();
	~PhongShader();

	virtual void VertexShader(SVertex& sVertex, int idx) override;
	virtual bool FragmentShader(Color& pColor, const Vertex3f& g,
								const SVertex v0, const SVertex v1, const SVertex v2) override;
};*/
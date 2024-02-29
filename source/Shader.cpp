#include "Shader.h"


// FlatShader
FlatShader::FlatShader() {}

FlatShader::~FlatShader() {
	mesh = nullptr;
	light = nullptr;
	delete mesh;
	delete light;
}

void FlatShader::VertexShader(SVertex& sVertex, int idx) {
	Vertex4f screenPos;

	sVertex.loc = cameraProjection * meshModelView * mesh->points[mesh->perFaceVertex[idx]].homogeneous();
	sVertex.uv = mesh->uv[mesh->perFaceVertexUV[idx]];
	sVertex.normal = mesh->normal[mesh->perFaceVertexNormal[idx]];
	sVertex.normal = squeeze<float, 3>(meshModelView * sVertex.normal.homogeneous()).normalize();
}

bool FlatShader::FragmentShader(Color& pColor, const Vertex3f& g, 
								const SVertex v0, const SVertex v1, const SVertex v2) {
	Vertex2f pUV = v0.uv * g.x + v1.uv * g.y + v2.uv * g.z;
	Vertex3f pNormal = v0.normal;
	Vertex3f lightDir = squeeze<float, 3>(lightModelView * light->dir.homogeneous()).normalize();
	float normalDotLightDir = max(0.0, vDot(lightDir, pNormal));
	if (normalDotLightDir < 0.0f) {
		return false;
	}
	pColor = mesh->texture.getTextureColor(pUV);
	pColor = light->color * pColor * normalDotLightDir;  // diffuse color
	return true;
}


// GouraudShader
/*GouraudShader::GouraudShader() {}

GouraudShader::~GouraudShader() {}

void GouraudShader::VertexShader(SVertex& sVertex, int idx) {
	Vertex4f screenPos;
	Matrix3f mat;
	ToMatrix3f(mat, transform.modelMat);

	sVertex.loc = mesh.points[mesh.perFaceVertex[idx]];
	sVertex.uv = mesh.uv[mesh.perFaceVertexUV[idx]];
	sVertex.color = mesh.texture.getTextureColor(sVertex.uv);

	sVertex.normal = { 0.0f, 0.0f, 0.0f };
	for (int i : mesh.preVertexForFace[mesh.perFaceVertex[idx]]) {
		for (int j : {0, 1, 2}) {
			sVertex.normal[j] += mesh.normal[i][j];
		}
	}
	sVertex.normal /= mesh.preVertexForFace[mesh.perFaceVertex[idx]].size();
	sVertex.normal = mat * sVertex.normal;
	sVertex.normal = sVertex.normal.normalize();

	Vertex3f lightDir = (lightPos - sVertex.loc).normalize();
	float normalDotLightDir = max(0.0, vDot(lightDir, sVertex.normal));
	sVertex.color = lightColor * sVertex.color * normalDotLightDir;  // diffuse color

	// projection
	screenPos = transform.viewportMat * transform.mvp * sVertex.loc.homogeneous();
	// perspective division
	sVertex.pixel = { screenPos.x / screenPos.w,
					  screenPos.y / screenPos.w,
					  screenPos.z / screenPos.w };
}

bool GouraudShader::FragmentShader(Color& pColor, const Vertex3f& g,
								   const SVertex v0, const SVertex v1, const SVertex v2) {
	
	pColor = v0.color * g.x + v1.color * g.y + v2.color * g.z;

	return true;
}

// PhongShader
PhongShader::PhongShader() {}

PhongShader::~PhongShader() {}

void PhongShader::VertexShader(SVertex& sVertex, int idx) {
	Vertex4f screenPos;
	Matrix3f mat;
	ToMatrix3f(mat, transform.modelMat);

	sVertex.loc = mesh.points[mesh.perFaceVertex[idx]];
	sVertex.uv = mesh.uv[mesh.perFaceVertexUV[idx]];
	sVertex.normal = mat * mesh.normal[mesh.perFaceVertexNormal[idx]];
	sVertex.color = mesh.texture.getTextureColor(sVertex.uv);

	Vertex3f lightDir = (lightPos - sVertex.loc).normalize();
	float normalDotLightDir = max(0.0, vDot(lightDir, sVertex.normal));
	sVertex.color = lightColor * sVertex.color * normalDotLightDir;  // diffuse color

	// projection
	screenPos = transform.viewportMat * transform.mvp * sVertex.loc.homogeneous();
	// perspective division
	sVertex.pixel = { screenPos.x / screenPos.w,
					  screenPos.y / screenPos.w,
					  screenPos.z / screenPos.w };
}

bool PhongShader::FragmentShader(Color& pColor, const Vertex3f& g,
								 const SVertex v0, const SVertex v1, const SVertex v2) {
	Vertex3f pixelNormal = (v0.normal * g.x + v1.normal * g.y + v2.normal * g.z).normalize();
	pColor = v0.color * g.x + v1.color * g.y + v2.color * g.z;

	return true;
}*/

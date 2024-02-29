#pragma once
#include "Texture.h"
#include "Object.h"

class Mesh: public Object {
public:
	Mesh() = default;
	~Mesh();
	void importObjModel(const std::wstring& meshName);

	std::vector<Vertex3f> points;
	std::vector<Vertex3f> normal;
	std::vector<Vertex2f> uv;
	std::vector<int> perFaceVertex;
	std::vector<int> perFaceVertexUV;
	std::vector<int> perFaceVertexNormal;
	std::vector<int> perFaceVertexNum;
	std::vector<std::vector<int>> preVertexForFace;
	Texture texture;
};

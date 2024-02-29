#include "Mesh.h"

/*
* Cube
*    1 ------ 5
*   /|       /|
*  / |      / |
* 3 ------ 7  |
* |  |     |  |
* |	 2 ----|- 6
* | /      | /
* |/       |/
* 4 ------ 8
*/

Mesh::~Mesh() {}

void Mesh::importObjModel(const std::wstring& meshName) {
	std::ifstream fileStream(rootPath + meshName);
	std::string line = "", tmp = "";
	int pointsCount = 0, faceIdx = -1;
	while (std::getline(fileStream, line)) {
		std::istringstream ins(line);
		char faceInfo;
		if (line[0] == 'v') {
			if (line[1] == 't') {
				Vertex2f vt{ 0, 0 };
				ins >> tmp >> vt[0] >> vt[1];
				uv.emplace_back(vt);
				//printf_s("%f, %f\n", vt[0], vt[1]);
			}
			else if (line[1] == 'n') {
				Vertex3f vn{ 0, 0, 0 };
				ins >> tmp >> vn[0] >> vn[1] >> vn[2];
				normal.emplace_back(vn);
				//printf_s("%f, %f, %f\n", vn[0], vn[1], vn[2]);
			}
			else {
				Vertex3f v{ 0, 0, 0 };
				ins >> tmp >> v[0] >> v[1] >> v[2];
				points.emplace_back(v);
				preVertexForFace.emplace_back(std::vector<int>{ });
				//printf_s("%f, %f, %f\n", v[1], v[2], v[3]);
			}
		}
		else if (line[0] == 'f') {
			std::vector<int> f{ 0, 0, 0 };
			ins >> faceInfo;
			int count = 0;
			while (ins >> f[0] >> faceInfo >> f[1] >> faceInfo >> f[2]) {
				// printf_s("%d, %d, %d\n", f[0], f[1], f[2]);
				perFaceVertex.emplace_back(f[0] - 1);
				perFaceVertexUV.emplace_back(f[1] - 1);
				perFaceVertexNormal.emplace_back(f[2] - 1);
				preVertexForFace[f[0] - 1].emplace_back(f[2] - 1);
				count += 1;
			}
			perFaceVertexNum.emplace_back(count);
		}
	}
	/*for (int i = 0; i < mesh.preVertexToFace.size(); i++) {
		printf_s("%d,%d,%d\n", mesh.preVertexToFace[i][0],
							   mesh.preVertexToFace[i][1],
							   mesh.preVertexToFace[i][2]);
	}*/
}
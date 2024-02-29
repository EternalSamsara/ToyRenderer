#pragma once
#include "Matrix.h"


// �������ļ�Ȩ
float computeFij(const Vertex3f& v0, const Vertex3f& v1, const Vertex3f& p);
// ������������
Vertex3f getBarycentric(const Vertex3f& v0, const Vertex3f& v1, const Vertex3f& v2, const Vertex3f& p);
bool judgePointInTriangle(const Vertex3f& v1, const Vertex3f& v2, const Vertex3f& v3, const Vertex3f& p);
// �ü�

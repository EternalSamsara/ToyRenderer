#pragma once
#include "Matrix.h"


// 计算重心加权
float computeFij(const Vertex3f& v0, const Vertex3f& v1, const Vertex3f& p);
// 计算重心坐标
Vertex3f getBarycentric(const Vertex3f& v0, const Vertex3f& v1, const Vertex3f& v2, const Vertex3f& p);
bool judgePointInTriangle(const Vertex3f& v1, const Vertex3f& v2, const Vertex3f& v3, const Vertex3f& p);
// 裁剪

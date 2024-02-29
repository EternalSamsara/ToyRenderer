#include "Geometry.h"


float computeFij(const Vertex3f& vi, const Vertex3f& vj, const Vertex3f& p) {
	return (vi.y - vj.y) * p.x + (vj.x - vi.x) * p.y + vi.x * vj.y - vj.x * vi.y;
}

Vertex3f getBarycentric(const Vertex3f& v0, const Vertex3f& v1, const Vertex3f& v2, const Vertex3f& p) {
	Vertex3f g;
	float f12 = 0.0f, f12p = 0.0f, f20 = 0.0f, f20p = 0.0f;  // f01 = 0.0f, f01p = 0.0f

	f12p = computeFij(v1, v2, p);
	f12 = computeFij(v1, v2, v0);
	f20p = computeFij(v2, v0, p);
	f20 = computeFij(v2, v0, v1);
	//f01p = computeFij(v0.loc, v1.loc, p);
	//f01 = computeFij(v0.loc, v1.loc, v2.loc);
	g.x = f12p / f12;
	g.y = f20p / f20;
	// c = f01p / f01;
	g.z = 1.0 - g.x - g.y;
	return g;
}

bool judgePointInTriangle(const Vertex3f& v1, const Vertex3f& v2, const Vertex3f& v3, const Vertex3f& p) {
	// Compute vectors        
	Vertex3f a = v1 - v2;
	Vertex3f b = v1 - v3;
	Vertex3f c = v1 - p;

	// Compute dot products
	float aa = vDot(a, a);
	float ab = vDot(a, b);
	float ac = vDot(a, c);
	float bb = vDot(b, b);
	float bc = vDot(b, c);

	// Compute barycentric coordinates
	float invDenom = 1 / (aa * bb - ab * ab);
	float u = (bb * ac - ab * bc) * invDenom;
	float v = (aa * bc - ab * ac) * invDenom;

	// Check whether point is in triangle
	return (u >= 0) && (v >= 0) && (u + v < 1);
}
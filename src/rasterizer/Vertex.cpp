
#include "rasterizer/Vertex.hpp"


Vertex	Vertex::mix(Vertex const &a, Vertex const &b, Vertex const &c, float u, float v, float w) {
	float	pu = u / a.position.w;
	float	pv = v / b.position.w;
	float	pw = w / c.position.w;
	float	pa = pu + pv + pw;
	Vertex	ret;

	pu /= pa;
	pv /= pa;
	pw /= pa;
	ret.position = a.position * u + b.position * v + c.position * w;
	ret.normal = a.normal * pu + b.normal * pv + c.normal * pw;
	return (ret);
}

Vertex	Vertex::mix(Vertex const &a, Vertex const &b, float t) {
	Vertex	ret;

	ret.position = a.position * (1 - t) + b.position * t;
	ret.normal = a.normal * (1 - t) + b.normal * t;
	return (ret);
}
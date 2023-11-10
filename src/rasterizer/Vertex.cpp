
#include "rasterizer/Vertex.hpp"


Vertex	Vertex::mix(Vertex const &a, Vertex const &b, Vertex const &c, _float u, _float v, _float w) {
	_float	pu = u / a.position.w;
	_float	pv = v / b.position.w;
	_float	pw = w / c.position.w;
	_float	pa = pu + pv + pw;
	Vertex	ret;

	pu /= pa;
	pv /= pa;
	pw /= pa;
	ret.position = a.position * u + b.position * v + c.position * w;
	ret.normal = a.normal * pu + b.normal * pv + c.normal * pw;
	return (ret);
}

Vertex	Vertex::mix(Vertex const &a, Vertex const &b, _float t) {
	Vertex	ret;

	ret.position = a.position * (-t + 1) + b.position * t;
	ret.normal = a.normal * (-t + 1) + b.normal * t;
	return (ret);
}
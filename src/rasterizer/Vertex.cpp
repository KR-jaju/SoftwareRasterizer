
#include "rasterizer/Vertex.hpp"


Vertex	Vertex::mix(Vertex const &a, Vertex const &b, Vertex const &c, float ratio_a, float ratio_b, float ratio_c) {
	Vertex	ret;

	ret.position = a.position * ratio_a + b.position * ratio_b + c.position * ratio_c;
	ret.normal = a.normal * ratio_a + b.normal * ratio_b + c.normal * ratio_c;
	return (ret);
}
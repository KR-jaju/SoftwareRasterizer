
#ifndef VERTEX_HPP
# define VERTEX_HPP

# include "math/Vector4.hpp"
# include "math/Vector3.hpp"

struct Vertex {
	Vector4	position;
	Vector3	normal;
	static Vertex	mix(Vertex const &a, Vertex const &b, Vertex const &c, _float ratio_a, _float ratio_b, _float ratio_c);
	static Vertex	mix(Vertex const &a, Vertex const &b, _float t);
};

#endif

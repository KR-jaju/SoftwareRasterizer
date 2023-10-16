
#ifndef VERTEX_HPP
# define VERTEX_HPP

# include "math/Vector4.hpp"
# include "math/Vector3.hpp"

struct Vertex {
	Vector4	position;
	Vector3	normal;
	static Vertex	mix(Vertex const &a, Vertex const &b, Vertex const &c, float ratio_a, float ratio_b, float ratio_c);
};

#endif

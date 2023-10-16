
#include "rasterizer/WeilerAthertonClipper.hpp"


WeilerAthertonClipper::~WeilerAthertonClipper() {}

void	WeilerAthertonClipper::clip(std::queue<Vertex> &out, Vertex const &a, Vertex const &b, Vertex const &c) {
	out.push(a);
	out.push(b);
	out.push(c);
}



#include "rasterizer/DefaultShader.hpp"

void	DefaultShader::vertex(Vertex const &in, Vertex &out) {
	(void) in;
	(void) out;
	out = in;
}

void	DefaultShader::fragment(Vertex const &in, int &color) {
	color = Color(0.0, 1.0, 1.0, 0.0);
	(void)in;
}
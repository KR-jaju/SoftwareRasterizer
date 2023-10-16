
#include "rasterizer/DefaultShader.hpp"

void	DefaultShader::vertex(Vertex const &in, Vertex &out) {
	//out.position = this->view * in.position;
	out.position = this->projection * (this->view * in.position);
	out.normal = in.normal;
}

void	DefaultShader::fragment(Vertex const &in, int &color) {
	// color = Color(0.0, 1.0, 1.0, 0.0);
	color = (Color)in.normal;
	(void)in;
}

void	DefaultShader::setViewMatrix(Matrix4x4 &m) {
	this->view = m;
}

void	DefaultShader::setProjectionMatrix(Matrix4x4 &m) {
	this->projection = m;
}


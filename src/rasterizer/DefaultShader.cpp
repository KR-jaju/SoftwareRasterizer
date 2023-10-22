
#include "rasterizer/DefaultShader.hpp"

void	DefaultShader::vertex(Vertex const &in, Vertex &out) {
	//out.position = this->view * in.position;
	out.position = this->projection * (this->view * in.position);
	out.normal = in.normal;
}

void	DefaultShader::fragment(Vertex const &in, Vector4 &color) {
	// color = Vector4(0.0, 1.0, 1.0, 0.0);
	// color = (Color)in.normal;
	color = Vector4(in.normal, 0.0);
	// color = Vector4(1, 1, 1, 0) * in.position.z;
	(void)in;
}

void	DefaultShader::setViewMatrix(Matrix4x4 &m) {
	this->view = m;
}

void	DefaultShader::setProjectionMatrix(Matrix4x4 &m) {
	this->projection = m;
}


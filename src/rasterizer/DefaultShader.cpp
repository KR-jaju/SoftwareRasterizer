
#include "rasterizer/DefaultShader.hpp"

DefaultShader::DefaultShader() {
	this->model.m[0][0] = 1;
	this->model.m[0][1] = 0;
	this->model.m[0][2] = 0;
	this->model.m[0][3] = 0;

	this->model.m[1][0] = 0;
	this->model.m[1][1] = 1;
	this->model.m[1][2] = 0;
	this->model.m[1][3] = 0;

	this->model.m[2][0] = 0;
	this->model.m[2][1] = 0;
	this->model.m[2][2] = 1;
	this->model.m[2][3] = 0;

	this->model.m[3][0] = 0;
	this->model.m[3][1] = 0;
	this->model.m[3][2] = 0;
	this->model.m[3][3] = 1;
}

void	DefaultShader::vertex(Vertex const &in, Vertex &out) {
	//out.position = this->view * in.position;
	// out.position = this->projection * (this->view * in.position);
	out.position = this->projection * (this->view * (this->model * in.position));
	out.normal = in.normal;
}

void	DefaultShader::fragment(Vertex const &in, Vector4 &color) {
	// color = Vector4(0.0, 1.0, 1.0, 0.0);
	// color = (Color)in.normal;
	color = Vector4(in.normal.normalized(), 0.0);
	// color = in.position;
	// color = Vector4(1, 1, 1, 0) * in.position.z;
	// color = color + Vector4(0.3, 0.3, 0.3, 0);
	(void)in;
}

void	DefaultShader::setModelMatrix(Matrix4x4 &m) {
	this->model = m;
}

void	DefaultShader::setViewMatrix(Matrix4x4 &m) {
	this->view = m;
}

void	DefaultShader::setProjectionMatrix(Matrix4x4 &m) {
	this->projection = m;
}


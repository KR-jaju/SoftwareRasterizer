#include "rasterizer/RenderTexture.hpp"

RenderTexture::RenderTexture(int width, int height) {
	this->width = width;
	this->height = height;
	this->color = new Vector4[width * height];
	this->depth = new _float[width * height];
}

void	RenderTexture::clear(Vector4 const &color, _float depth) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			this->color[x + y * width] = color;
			this->depth[x + y * width] = depth;
		}
	}
}

RenderTexture::~RenderTexture() {
	delete[] this->color;
	delete[] this->depth;
}

Vector4	&RenderTexture::pixelColor(int x, int y) {
	return (this->color[x + y * this->width]);
}

_float	&RenderTexture::pixelDepth(int x, int y) {
	return (this->depth[x + y * this->width]);
}

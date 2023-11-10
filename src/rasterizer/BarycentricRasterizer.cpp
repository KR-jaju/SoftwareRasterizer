
#include "rasterizer/BarycentricRasterizer.hpp"
#include "math/Vector3.hpp"
#include "math/Color.hpp"
#include "rasterizer/Shader.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

BarycentricRasterizer::BarycentricRasterizer(int width, int height) {
	this->width = width;
	this->height = height;
	this->target = nullptr;
	this->test_depth = true;
}

BarycentricRasterizer::~BarycentricRasterizer() {}

static
_float	min(_float a, _float b, _float c) {
	if (a > b)
		a = b;
	if (a > c)
		a = c;
	return (a);
}

static
_float	max(_float a, _float b, _float c) {
	if (a < b)
		a = b;
	if (a < c)
		a = c;
	return (a);
}

static
inline Vertex	toNDC(Vertex const &clip_space) {
	Vertex	ret;
	_float one;

	one.setNumber(1);
	ret = clip_space;
	ret.position.x /= ret.position.w;
	ret.position.y /= ret.position.w;
	ret.position.z /= ret.position.w;
	ret.position.w = one / ret.position.w;
	return (ret);
}

static
inline Vector4	toScreenSpace(Vector4 a, int width, int height) {
	a.x = (a.x * 0.5f + 0.5f) * width + 0.5f;
	a.y = (-a.y * 0.5f + 0.5f) * height + 0.5f;
	return (a);
}

static
inline _float	cross(Vector4 &a, Vector4 &b, Vector4 &c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool	BarycentricRasterizer::depthTest(int x, int y, Vertex const &fragment) {
	_float	&storedDepth = this->target->pixelDepth(x, y);

	if (storedDepth <= fragment.position.z)
		return (false);
	storedDepth = fragment.position.z;
	return (true);
}

void	BarycentricRasterizer::drawTriangle(Vertex &a, Vertex &b, Vertex &c, Shader *shader) {
	Vector4	screen_a = toScreenSpace(a.position, this->width, this->height);
	Vector4	screen_b = toScreenSpace(b.position, this->width, this->height);
	Vector4 screen_c = toScreenSpace(c.position, this->width, this->height);
	int		x_min = std::max(static_cast<int>(min(screen_a.x, screen_b.x, screen_c.x).round().getReal()), 0);
	int		x_max = std::min(static_cast<int>(max(screen_a.x, screen_b.x, screen_c.x).round().getReal()), this->width - 1);
	int		y_min = std::max(static_cast<int>(min(screen_a.y, screen_b.y, screen_c.y).round().getReal()), 0);
	int		y_max = std::min(static_cast<int>(max(screen_a.y, screen_b.y, screen_c.y).round().getReal()), this->height - 1);
	_float	area = cross(screen_a, screen_b, screen_c);

	for (int y = y_min; y <= y_max; y++) {
		for (int x = x_min; x <= x_max; x++) {
			Vector4	p(x, y, 0, 1);
			_float	u = cross(screen_b, screen_c, p) / area;
			_float	v = cross(screen_c, screen_a, p) / area;
			_float	w = -u - v + 1;
			if (u >= 0 && u <= 1 && v >= 0 && v <= 1 && w >= 0 && w <= 1) {
				Vertex	fragment = Vertex::mix(a, b, c, u, v, w);
				if (this->test_depth && !this->depthTest(x, y, fragment))
					continue;
				shader->fragment(fragment, this->target->pixelColor(x, y));
			}
		}
	}
}

void	BarycentricRasterizer::drawPolygon(std::queue<Vertex> &polygon, Shader *shader) {
	if (polygon.empty())
		return ;
	Vertex	root = toNDC(polygon.front());
	polygon.pop();
	Vertex	prev = toNDC(polygon.front());
	polygon.pop();
	while (!polygon.empty()) {
		Vertex	curr = toNDC(polygon.front());
		polygon.pop();
		this->drawTriangle(root, curr, prev, shader);
		prev = curr;
	}
}

void	BarycentricRasterizer::draw(Mesh &mesh, int count, Shader *shader, Clipper *clipper) {
	std::queue<Vertex>	polygon;
	Vertex				tmp;

	if (this->target == nullptr)
		return ;
	for (int i = 0; i + 3 <= count; i += 3) {
		for (int j = 0; j < 3; j++) {
			shader->vertex(mesh[i + j], tmp);
			polygon.push(tmp);
		}
		clipper->clip(polygon);
		this->drawPolygon(polygon, shader);
	}
}

void	BarycentricRasterizer::setTarget(RenderTexture *rt) {
	this->target = rt;
}

void	BarycentricRasterizer::blit(int *dst) {
	if (this->target == nullptr)
		return ;
	for (int y = 0; y < this->height; y++)
		for (int x = 0; x < this->width; x++)
			dst[x + y * this->width] = (Color)this->target->pixelColor(x, y);
}

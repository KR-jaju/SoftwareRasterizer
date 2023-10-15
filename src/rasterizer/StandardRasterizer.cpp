
#include "rasterizer/BarycentricRasterizer.hpp"
#include "math/Vector3.hpp"
#include <cmath>

BarycentricRasterizer::BarycentricRasterizer(int width, int height) {
	this->width = width;
	this->height = height;
	this->color = new int[width * height];
	this->depth = new float[width * height];
}

BarycentricRasterizer::~BarycentricRasterizer() {
	delete[] this->color;
	delete[] this->depth;
}

static
float	min(float a, float b, float c) {
	if (a > b)
		a = b;
	if (a > c)
		a = c;
	return (a);
}

static
float	max(float a, float b, float c) {
	if (a < b)
		a = b;
	if (a < c)
		a = c;
	return (a);
}

// static
// inline void	toNDC(Vector3 &a, int width, int height) {
// 	a.x = ((a.x - 0.5f) / width) * 2 - 1;
// 	a.y = ((a.y - 0.5f) / height) * 2 - 1;
// }

static
inline Vector3	toScreenSpace(Vector3 a, int width, int height) {
	a.x = (a.x * 0.5f + 0.5f) * width + 0.5f;
	a.y = (-a.y * 0.5f + 0.5f) * height + 0.5f;
	return (a);
}

static
inline float	cross(Vector3 &a, Vector3 &b, Vector3 &c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

void	BarycentricRasterizer::drawTriangle(Vertex &a, Vertex &b, Vertex &c) {
	Vector3	screen_a = toScreenSpace(a.position, this->width, this->height);
	Vector3	screen_b = toScreenSpace(b.position, this->width, this->height);
	Vector3 screen_c = toScreenSpace(c.position, this->width, this->height);
	int		x_min = static_cast<int>(roundf(min(screen_a.x, screen_b.x, screen_c.x)));
	int		x_max = static_cast<int>(roundf(max(screen_a.x, screen_b.x, screen_c.x)));
	int		y_min = static_cast<int>(roundf(min(screen_a.y, screen_b.y, screen_c.y)));
	int		y_max = static_cast<int>(roundf(max(screen_a.y, screen_b.y, screen_c.y)));
	float	area = cross(screen_a, screen_b, screen_c);

	for (int y = y_min; y <= y_max; y++) {
		for (int x = x_min; x <= x_max; x++) {
			Vector3	p(x, y, 0);
			float	u = cross(screen_b, screen_c, p) / area;
			float	v = cross(screen_c, screen_a, p) / area;
			float	w = 1 - u - v;
			if (0 <= u && u <= 1 && 0 <= v && v <= 1 && 0 <= w && w <= 1)
				this->color[x + y * this->width] = 0x00ffffff;
			else
				this->color[x + y * this->width] = 0x00000000;
		}
	}
}

void	BarycentricRasterizer::draw(Mesh &mesh, int count) {
	for (int i = 0; i + 3 <= count; i += 3) {
		this->drawTriangle(mesh.get(i), mesh.get(i + 1), mesh.get(i + 2));
	}
}

void	BarycentricRasterizer::blit(int *dst) {
	for (int y = 0; y < this->height; y++)
		for (int x = 0; x < this->width; x++)
			dst[x + y * this->width] = this->color[x + y * this->width];
}

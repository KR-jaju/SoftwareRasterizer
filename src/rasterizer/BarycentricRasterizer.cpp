
#include "rasterizer/BarycentricRasterizer.hpp"
#include "math/Vector3.hpp"
#include "math/Color.hpp"
#include "rasterizer/Shader.hpp"
#include <cmath>
#include <algorithm>

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
inline Vector4	toScreenSpace(Vector4 a, int width, int height) {
	a.x = (a.x * 0.5f + 0.5f) * width + 0.5f;
	a.y = (-a.y * 0.5f + 0.5f) * height + 0.5f;
	return (a);
}

static
inline float	cross(Vector4 &a, Vector4 &b, Vector4 &c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

void	BarycentricRasterizer::drawTriangle(Vertex &a, Vertex &b, Vertex &c, Shader *shader) {
	Vector4	screen_a = toScreenSpace(a.position, this->width, this->height);
	Vector4	screen_b = toScreenSpace(b.position, this->width, this->height);
	Vector4 screen_c = toScreenSpace(c.position, this->width, this->height);
	int		x_min = std::max(static_cast<int>(roundf(min(screen_a.x, screen_b.x, screen_c.x))), 0);
	int		x_max = std::min(static_cast<int>(roundf(max(screen_a.x, screen_b.x, screen_c.x))), this->width - 1);
	int		y_min = std::max(static_cast<int>(roundf(min(screen_a.y, screen_b.y, screen_c.y))), 0);
	int		y_max = std::min(static_cast<int>(roundf(max(screen_a.y, screen_b.y, screen_c.y))), this->height - 1);
	float	area = cross(screen_a, screen_b, screen_c);

	for (int y = y_min; y <= y_max; y++) {
		for (int x = x_min; x <= x_max; x++) {
			Vector4	p(x, y, 0, 1);
			float	u = cross(screen_b, screen_c, p) / area;
			float	v = cross(screen_c, screen_a, p) / area;
			float	w = 1 - u - v;
			if (0 <= u && u <= 1 && 0 <= v && v <= 1 && 0 <= w && w <= 1) {
				float	pu = u / a.position.w;
				float	pv = v / b.position.w;
				float	pw = w / c.position.w;
				float	pa = pu + pv + pw;
				Vertex	fragment = Vertex::mix(a, b, c, pu / pa,  pv / pa, pw / pa);
				shader->fragment(fragment, this->color[x + y * this->width]);
			}
		}
	}
}

void	BarycentricRasterizer::draw(Mesh &mesh, int count, Shader *shader) {
	Vertex	clip_space[3];

	for (int i = 0; i + 3 <= count; i += 3) {
		shader->vertex(mesh[i], clip_space[0]);
		shader->vertex(mesh[i + 1], clip_space[1]);
		shader->vertex(mesh[i + 2], clip_space[2]);
		clip_space[0].position = clip_space[0].position / clip_space[0].position.w;
		clip_space[1].position = clip_space[1].position / clip_space[1].position.w;
		clip_space[2].position = clip_space[2].position / clip_space[2].position.w;
		this->drawTriangle(clip_space[0], clip_space[1], clip_space[2], shader);
	}
}

void	BarycentricRasterizer::blit(int *dst) {
	for (int y = 0; y < this->height; y++)
		for (int x = 0; x < this->width; x++)
			dst[x + y * this->width] = this->color[x + y * this->width];
}


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
	for (int i = 0; i < width * height; i++)
		this->depth[i] = 1;
	this->target = 0;
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

static
inline Vertex	toNDC(Vertex const &clip_space) {
	Vertex	ret;

	ret = clip_space;
	ret.position.x /= ret.position.w;
	ret.position.y /= ret.position.w;
	ret.position.z /= ret.position.w;
	return (ret);
}

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

bool	BarycentricRasterizer::depthTest(int x, int y, Vertex const &fragment) {
	float	&storedDepth = this->target->pixelDepth(x, y);
	// this->depth[x + y * this->width];

	if (storedDepth <= fragment.position.z)
		return (false);
	storedDepth = fragment.position.z;
	return (true);
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
				Vertex	fragment = Vertex::mix(a, b, c, u, v, w);
				if (!this->depthTest(x, y, fragment))
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

	if (this->target == 0)
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
	if (this->target == 0)
		return ;
	for (int y = 0; y < this->height; y++)
		for (int x = 0; x < this->width; x++)
			dst[x + y * this->width] = (Color)this->target->pixelColor(x, y);
			//this->color[x + y * this->width];
}

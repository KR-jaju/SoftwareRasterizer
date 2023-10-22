#include "rasterizer/StandardRasterizer.hpp"
#include "math/Vector3.hpp"
#include <cmath>
#include <vector>

int min(int x1, int x2)
{
	if (x1 < x2)
		return x1;
	return x2;
}

int max(int x1, int x2)
{
	if (x1 > x2)
		return x1;
	return x2;
}

static
inline float cross(Vector4 &a, Vector4 &b, Vector4 &c) 
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

static
inline Vector4	toScreenSpace(Vector4 a, int width, int height) 
{
	a.x = (a.x * 0.5f + 0.5f) * width + 0.5f;
	a.y = (-a.y * 0.5f + 0.5f) * height + 0.5f;
	return (a);
}

bool StandardRasterizer::depthTest(int y, int x, Vertex &fragment)
{
	float &storedDepth = target->pixelDepth(x, y);
	if (storedDepth <= fragment.position.z)
		return false;
	storedDepth = fragment.position.z;
	return true;
}

void StandardRasterizer::drawTriangle(Vertex &a, Vertex &b, Vertex &c, Shader *shader)
{
	Vector4 tmp_a = toScreenSpace(a.position, this->width, this->height);
	Vector4 tmp_b = toScreenSpace(b.position, this->width, this->height);
	Vector4 tmp_c = toScreenSpace(c.position, this->width, this->height);
	float slope1 = (tmp_a.x - tmp_b.x) / (tmp_a.y - tmp_b.y);
	float slope2 = (tmp_a.x - tmp_c.x) / (tmp_a.y - tmp_c.y);

	float tmpX = tmp_a.x;
	float tmpX2 = tmpX;

	float u, v, w, area;
	area = cross(tmp_a, tmp_b, tmp_c);
	for (int i = int(tmp_a.y); i <= int(tmp_b.y); i++)
	{
		if (i < 0 || i > height) continue;
		for (int j = min(tmpX, tmpX2); j <= max(tmpX, tmpX2); j++)
		{	
			if (j < 0 || j > width) continue;
			Vector4 p(j, i, 0, 0);
			u = cross(tmp_b, tmp_c, p) / area;
			v = cross(tmp_c, tmp_a, p) / area;
			w = 1 - u - v;
			Vertex fragment = Vertex::mix(a, b, c, u, v, w);
			if (depthTest(i, j, fragment) == false) continue;
			shader->fragment(fragment, this->target->pixelColor(j, i));
		}
		tmpX += slope1;
		tmpX2 += slope2;
	}

	slope1 = (tmp_c.x - tmp_b.x) / (tmp_c.y - tmp_b.y);
	tmpX = tmp_c.x;
	tmpX2 = tmpX;
	for (int i = int(tmp_c.y); i >= int(tmp_b.y); i--)
	{
		if (i < 0 || i > height) continue;
		for (int j = min(tmpX, tmpX2); j <= max(tmpX, tmpX2); j++)
		{
			if (j < 0 || j > width) continue;
			Vector4 p(j, i, 0, 0);
			u = cross(tmp_b, tmp_c, p) / area;
			v = cross(tmp_c, tmp_a, p) / area;
			w = 1 - u - v;
			Vertex fragment = Vertex::mix(a, b, c, u, v, w);
			if (depthTest(i, j, fragment) == false) continue;
			shader->fragment(fragment, this->target->pixelColor(j, i));
		}
		tmpX -= slope1;
		tmpX2 -= slope2;
	}
}

StandardRasterizer::StandardRasterizer(int width, int height)
{
	this->width = width;
	this->height = height;
	this->target = 0;
}

StandardRasterizer::~StandardRasterizer()
{
}
void	StandardRasterizer::setTarget(RenderTexture *rt) {
	this->target = rt;
}

static bool cmp(Vertex &v1, Vertex &v2)
{
	if (v1.position.y < v2.position.y)
		return false;
	return true;
}

static
inline Vertex toNDC(Vertex clip_space)
{
	clip_space.position.x /= clip_space.position.w;
	clip_space.position.y /= clip_space.position.w;
	clip_space.position.z /= clip_space.position.w;
	return clip_space;
}

void StandardRasterizer::drawPolygon(std::queue<Vertex> &polygon, Shader *shader)
{
	std::vector<Vertex> vec;

	Vertex root = toNDC(polygon.front());
	polygon.pop();
	Vertex prev = toNDC(polygon.front());
	polygon.pop();
	Vertex curr;
	while(polygon.size())
	{
		curr = toNDC(polygon.front());
		polygon.pop();
		vec.clear();
		vec.push_back(root);
		vec.push_back(prev);
		vec.push_back(curr);
		std::sort(vec.begin(), vec.end(), cmp);
		drawTriangle(vec[0], vec[1], vec[2], shader);
		prev = curr;
	}
}

void StandardRasterizer::draw(Mesh &mesh, int count, Shader *shader, Clipper *clipper)
{
	std::queue<Vertex> polygon;
	Vertex tmp;

	if (this->target == 0)
		return ;
	for (int i = 0; i + 3 <= count; i += 3)
	{
		for (int j = i; j < i + 3; j++)
		{
			shader->vertex(mesh[i + j], tmp);
			polygon.push(tmp);
		}
		clipper->clip(polygon);
		drawPolygon(polygon, shader);
	}
}

void StandardRasterizer::blit(int *dst)
{
	if (this->target == 0)
		return ;
	for (int y = 0; y < this->height; y++)
		for (int x = 0; x < this->width; x++)
			dst[x + y * this->width] = (Color)this->target->pixelColor(x, y);
}
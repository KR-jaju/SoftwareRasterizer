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

bool StandardRasterizer::depthTest(float d, int idx)
{
	if (depth[idx] > d)
	{
		depth[idx] = d;
		return true;
	}
	return false;
}

void StandardRasterizer::drawTriangle(Vertex &a, Vertex &b, Vertex &c, Shader *shader)
{
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
			this->color[j + i * this->width] = 0x00000000;
	
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
			if (depthTest(fragment.position.z, j + this->width * i) == false) continue;
			shader->fragment(fragment, this->target->pixelColor(j, i));
			//color[j + this->width * i]);
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
			if (depthTest(fragment.position.z, j + this->width * i) == false) continue;
			shader->fragment(fragment, this->target->pixelColor(j, i));
			//shader->fragment(fragment, color[j + this->width * i]);
		}
		tmpX -= slope1;
		tmpX2 -= slope2;
	}
}

StandardRasterizer::StandardRasterizer(int width, int height)
{
	this->width = width;
	this->height = height;
	this->color = new int[width * height];
	this->depth = new float[width * height];
	for (int i = 0; i < width * height; i++)
		depth[i] = 1;
}

StandardRasterizer::~StandardRasterizer()
{
	delete[] this->color;
	delete[] this->depth;
}

static bool cmp(Vertex &v1, Vertex &v2)
{
	if (v1.position.y < v2.position.y)
		return false;
	return true;
}

void StandardRasterizer::draw(Mesh &mesh, int count, Shader *shader, Clipper *clipper)
{
	(void) shader;
	(void) clipper;
	std::vector<Vertex> vec;
	for (int i = 0; i + 3 <= count; i += 3)
	{
		vec.clear();
		for (int j = i; j < i + 3; j++)
			vec.push_back(mesh.get(j));
		std::sort(vec.begin(), vec.end(), cmp);
		this->drawTriangle(vec[0], vec[1], vec[2], shader);
	}
}

void StandardRasterizer::blit(int *dst)
{
	for (int y = 0; y < this->height; y++)
		for (int x = 0; x < this->width; x++)
			dst[x + y * this->width] = this->color[x + y * this->width];
}
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
inline Vector3	toScreenSpace(Vector3 a, int width, int height) 
{
	a.x = (a.x * 0.5f + 0.5f) * width + 0.5f;
	a.y = (-a.y * 0.5f + 0.5f) * height + 0.5f;
	return (a);
}

void StandardRasterizer::drawTriangle(Vertex &a, Vertex &b, Vertex &c)
{
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
			this->color[j + i * this->width] = 0x00000000;
	
	Vector3 tmp_a = toScreenSpace(a.position, this->width, this->height);
	Vector3 tmp_b = toScreenSpace(b.position, this->width, this->height);
	Vector3 tmp_c = toScreenSpace(c.position, this->width, this->height);
	float slope1 = (tmp_a.x - tmp_b.x) / (tmp_a.y - tmp_b.y);
	float slope2 = (tmp_a.x - tmp_c.x) / (tmp_a.y - tmp_c.y);

	float tmpX = tmp_a.x;
	float tmpX2 = tmpX;
	for (int i = int(tmp_a.y); i <= int(tmp_b.y); i++)
	{
		for (int j = min(tmpX, tmpX2); j <= max(tmpX, tmpX2); j++)
			color[j + this->width * i] = 0x0000FF00;
		tmpX += slope1;
		tmpX2 += slope2;
	}

	slope1 = (tmp_c.x - tmp_b.x) / (tmp_c.y - tmp_b.y);
	tmpX = tmp_c.x;
	tmpX2 = tmpX;
	for (int i = int(tmp_c.y); i >= int(tmp_b.y); i--)
	{
		for (int j = min(tmpX, tmpX2); j <= max(tmpX, tmpX2); j++)
			color[j + this->width * i] = 0X0000FF00;
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
}

StandardRasterizer::~StandardRasterizer()
{
	delete[] this->color;
	delete[] this->depth;
}


static
inline float crossWidth(Vector3 &a, Vector3 &b, Vector3 &c) 
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

static bool cmp(Vertex &v1, Vertex &v2)
{
	if (v1.position.y < v2.position.y)
		return true;
	return false;
}

void StandardRasterizer::draw(Mesh &mesh, int count)
{
	std::vector<Vertex> vec;
	for (int i = 0; i + 3 <= count; i += 3)
	{
		vec.clear();
		for (int j = i; j < i + 3; j++)
			vec.push_back(mesh.get(i));
		std::sort(vec.begin(), vec.end(), cmp);
		this->drawTriangle(vec[0], vec[1], vec[2]);
	}
}

void StandardRasterizer::blit(int *dst)
{
	for (int y = 0; y < this->height; y++)
		for (int x = 0; x < this->width; x++)
			dst[x + y * this->width] = this->color[x + y * this->width];
}
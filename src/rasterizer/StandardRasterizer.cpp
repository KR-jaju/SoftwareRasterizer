#include "rasterizer/StandardRasterizer.hpp"
#include "math/Vector3.hpp"
#include <cmath>
#include <vector>
#include <iostream>

static
int min(int x1, int x2)
{
	if (x1 < x2)
		return x1;
	return x2;
}

static
int max(int x1, int x2)
{
	if (x1 > x2)
		return x1;
	return x2;
}

static
bool cmp(Vertex &v1, Vertex &v2)
{
	if (v1.position.y < v2.position.y)
		return false;
	if (v1.position.y.same(v2.position.y, 0))
	{
		return v1.position.x < v2.position.x;
	}
	return true;
}

static
inline _float cross(Vector4 &a, Vector4 &b, Vector4 &c) 
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

static
inline Vector4	toScreenSpace(Vector4 a, int width, int height) 
{
	a.x = (a.x * 0.5f + 0.5f) * width;
	a.y = (-a.y * 0.5f + 0.5f) * height;
	return (a);
}

bool StandardRasterizer::depthTest(int y, int x, Vertex &fragment)
{
	_float &storedDepth = target->pixelDepth(x, y);
	if (storedDepth <= fragment.position.z)
		return false;
	storedDepth = fragment.position.z;
	return true;
}

static
int	roundUpInt(_float a) {
	return int(a.round().getReal());
}

static
int	roundDownInt(_float a) {
	_float res = -a + 1;
	return int((-res.round() + 1).getReal());
}

void StandardRasterizer::drawTriangle(Vertex &a, Vertex &b, Vertex &c, Shader *shader)
{
	std::vector<Vertex> vec;
	vec.push_back(a);
	vec.push_back(b);
	vec.push_back(c);
	sort(vec.begin(), vec.end(), cmp);

	Vector4 tmp_a = toScreenSpace(vec[0].position, this->width, this->height);
	Vector4 tmp_b = toScreenSpace(vec[1].position, this->width, this->height);
	Vector4 tmp_c = toScreenSpace(vec[2].position, this->width, this->height);
	_float slope1 = (tmp_a.x - tmp_b.x) / (tmp_a.y - tmp_b.y);
	_float slope2 = (tmp_a.x - tmp_c.x) / (tmp_a.y - tmp_c.y);

	_float tmpX = tmp_a.x;
	_float tmpX2 = tmpX;

	_float u, v, w, area;
	area = cross(tmp_a, tmp_b, tmp_c);

	if (tmp_a.y.same(tmp_b.y, 0.0001) == false)
	{
		for (int i = roundDownInt(tmp_a.y); i < roundDownInt(tmp_b.y); i++)
		{
			int	from, to;
			tmpX = tmp_a.x + slope1 * (-tmp_a.y + i + 0.5);
			tmpX2 = tmp_a.x + slope2 * (-tmp_a.y + i + 0.5);

			from = min(roundDownInt(tmpX), roundDownInt(tmpX2));
			to = max(roundDownInt(tmpX), roundDownInt(tmpX2));
			for (int j = from; j < to; j++)
			{
				Vector4 p(j + 0.5, i + 0.5, 0, 1);
				u = cross(tmp_b, tmp_c, p) / area;
				v = cross(tmp_c, tmp_a, p) / area;
				w = -u - v + 1;
				Vertex fragment = Vertex::mix(vec[0], vec[1], vec[2], u, v, w);
				if (depthTest(i, j, fragment) == false) continue;
				shader->fragment(fragment, this->target->pixelColor(j, i));
			}
		}
	}

	slope1 = (tmp_c.x - tmp_b.x) / (tmp_c.y - tmp_b.y);
	if (tmp_c.y.same(tmp_b.y, 0.0001) == true)
		return ;
	for (int i = roundUpInt(tmp_c.y) - 1; i >= roundDownInt(tmp_b.y); i--)
	{
		int	from, to;
		tmpX = tmp_c.x + slope1 * (-tmp_c.y + i + 0.5);
		tmpX2 = tmp_c.x + slope2 * (-tmp_c.y + i + 0.5);
		from = min(roundDownInt(tmpX), roundDownInt(tmpX2));
		to = max(roundDownInt(tmpX), roundDownInt(tmpX2));
		for (int j = from; j < to; j++)
		{
			Vector4	p(j + 0.5, i + 0.5, 0, 1);
			u = cross(tmp_b, tmp_c, p) / area;
			v = cross(tmp_c, tmp_a, p) / area;
			w = -u - v + 1;
			Vertex	fragment = Vertex::mix(vec[0], vec[1], vec[2], u, v, w);
			if (depthTest(i, j, fragment) == false) continue;
			shader->fragment(fragment, this->target->pixelColor(j, i));
		}
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

static
inline Vertex toNDC(Vertex clip_space)
{
	_float one;
	one.setNumber(1);
	clip_space.position.x /= clip_space.position.w;
	clip_space.position.y /= clip_space.position.w;
	clip_space.position.z /= clip_space.position.w;
	clip_space.position.w = one / clip_space.position.w;
	return clip_space;
}

void StandardRasterizer::drawPolygon(std::queue<Vertex> &polygon, Shader *shader)
{
	if (polygon.empty())
		return ;
	Vertex root = toNDC(polygon.front());
	polygon.pop();
	Vertex prev = toNDC(polygon.front());
	polygon.pop();
	Vertex curr;
	while(polygon.size())
	{
		curr = toNDC(polygon.front());
		polygon.pop();
		drawTriangle(root, prev, curr, shader);
		prev = curr;
	}
}

void StandardRasterizer::draw(Mesh &mesh, int count, Shader *shader, Clipper *clipper)
{
	std::queue<Vertex> polygon;
	Vertex tmp;
	float cnt = 0;
	float percent = 1;
	if (this->target == 0)
		return ;
	for (int i = 0; i + 3 <= count; i += 3)
	{
		for (int j = 0; j < 3; j++)
		{
			shader->vertex(mesh[i + j], tmp);
			polygon.push(tmp);
		}
		clipper->clip(polygon);
		drawPolygon(polygon, shader);
		cnt++;
		if (cnt >= (mesh.getSize() / 3.0) * (percent / 10.0))
		{
			std::cout << percent * 10 << "\% complete......" << std::endl;
			percent++;
		}
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
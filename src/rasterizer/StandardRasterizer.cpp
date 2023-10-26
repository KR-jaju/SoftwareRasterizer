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
	return true;
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

static
int roundFloat(float x)
{
	float check = x - int(x);
	if (check > 0.5)
		return int(x) + 1;
	return int(x);
}

// static
// std::vector<Vector4> Brasenham(Vector4 p1, Vector4 p2)
// {
// 	std::vector<Vector4> res;
// 	int	dx;
// 	int	dy;
// 	const int inc_x = (p1.x > p2.x ? -1 : 1);
// 	const int inc_y = (p1.y > p2.y ? -1 : 1);
// 	Vector4 tmp;

// 	dx = roundFloat(abs(p1.x - p2.x));
// 	dy = roundFloat((abs(p1.y - p2.y)));
// 	if (dy <= dx)
// 	{
// 		int p = 2 * dy - dx;
// 		int y = roundFloat(p1.y);
// 		float t, z;
// 		res.push_back(Vector4(roundFloat(p1.x), y, 0, 0));
// 		if (p1.x <= p2.x)
// 		{
// 			for (int x = roundFloat(p1.x); x <= roundFloat(p2.x); x += inc_x)
// 			{
// 				if (0 >= p)
// 					p += 2 * dy;
// 				else
// 				{
// 					p += 2 * dy - 2 * dx;
// 					y += inc_y;
// 				}
// 				if (roundFloat(res[res.size() - 1].y) == y)
// 					res.pop_back();
// 				t = abs(float(x) - p1.x) / abs(float(p2.x) - p1.x);
// 				z = t * p2.z + (1 - t) * p1.z;
// 				res.push_back(Vector4(x, y, z, 1));
// 			}
// 		}
// 		else
// 		{
// 			for (int x = roundFloat(p1.x); x >= roundFloat(p2.x); x += inc_x)
// 			{
// 				if (0 >= p)
// 					p += 2 * dy;
// 				else
// 				{
// 					p += 2 * dy - 2 * dx;
// 					y += inc_y;
// 				}
// 				if (roundFloat(res[res.size() - 1].y) == y)
// 					res.pop_back();
// 				t = abs(float(x) - p1.x) / abs(float(p2.x) - p1.x);
// 				z = t * p2.z + (1 - t) * p1.z;
// 				res.push_back(Vector4(x, y, z, 1));
// 			}
// 		}
// 	}
// 	else
// 	{
// 		int p = 2 * dy - dx;
// 		int x = roundFloat(p1.x);
// 		float t, z;
// 		res.push_back(Vector4(x, roundFloat(p1.y), 0, 0));
// 		if (p1.y <= p2.y)
// 		{
// 			for (int y = roundFloat(p1.y); y <= roundFloat(p2.y); y += inc_y)
// 			{
// 				if (0 >= p)
// 					p += 2 * dx;
// 				else
// 				{
// 					p += 2 * dx - 2 * dy;
// 					x += inc_x;
// 				}
// 				t = abs(float(x) - p1.x) / abs(float(p2.x) - p1.x);
// 				z = t * p2.z + (1 - t) * p1.z;
// 				res.push_back(Vector4(x, y, z, 1));
// 			}
// 		}
// 		else
// 		{
// 			for (int y = roundFloat(p1.y); y >= roundFloat(p2.y); y += inc_y)
// 			{
// 				if (0 >= p)
// 					p += 2 * dx;
// 				else
// 				{
// 					p += 2 * dx - 2 * dy;
// 					x += inc_x;
// 				}
// 				t = abs(float(x) - p1.x) / abs(float(p2.x) - p1.x);
// 				z = t * p2.z + (1 - t) * p1.z;
// 				res.push_back(Vector4(x, y, z, 1));
// 			}
// 		}
// 	}
// 	return res;
// }

// static
// Vector4 findInterpolation(Vector4 &a, Vector4 &c, Vector4 &b)
// {
// 	float t = (b.y - a.y) / (c.y - a.y);
// 	float x = t * c.x + (1 - t) * a.x;
// 	float z = t * c.z + (1 - t) * a.z;
// 	return Vector4(x, b.y, z, 1);
// }

// void StandardRasterizer::drawTriangle(Vertex &a, Vertex &b, Vertex &c, Shader *shader)
// {
// 	std::vector<Vertex> vec;
// 	std::vector<Vector4> upTrianglePixelsLeft, upTrianglePixelsRight;
// 	std::vector<Vector4> downTrianglePixelsLeft, downTrianglePixelsRight;
// 	vec.push_back(a);
// 	vec.push_back(b);
// 	vec.push_back(c);
// 	sort(vec.begin(), vec.end(), cmp);

// 	Vector4 tmp_a = toScreenSpace(vec[0].position, this->width, this->height);
// 	Vector4 tmp_b = toScreenSpace(vec[1].position, this->width, this->height);
// 	Vector4 tmp_c = toScreenSpace(vec[2].position, this->width, this->height);
// 	Vector4 tmp_d = findInterpolation(tmp_a, tmp_c, tmp_b);
// 	float u, v, w, area;

// 	area = cross(tmp_a, tmp_b, tmp_c);
// 	upTrianglePixelsLeft = Brasenham(tmp_a, tmp_b);
// 	upTrianglePixelsRight = Brasenham(tmp_a, tmp_d);
// 	if (tmp_a.x != tmp_d.x || tmp_a.y != tmp_d.y)
// 	{
// 		for (int i = 0; i < int(upTrianglePixelsLeft.size()) - 1; i++)
// 		{
// 			int start, end;
// 			if (i == int(upTrianglePixelsRight.size()))
// 				break;
// 			if (upTrianglePixelsLeft[i].x <= upTrianglePixelsRight[i].x)
// 			{
// 				start = upTrianglePixelsLeft[i].x;
// 				end = upTrianglePixelsRight[i].x;
// 			}
// 			else
// 			{
// 				start = upTrianglePixelsRight[i].x;
// 				end = upTrianglePixelsLeft[i].x;
// 			}
// 			for (int j = start; j < end; j++)
// 			{
// 				Vector4 p(j, i, 0, 1);
// 				u = cross(tmp_b, tmp_c, p) / area;
// 				v = cross(tmp_c, tmp_a, p) / area;
// 				w = 1 - u - v;
// 				Vertex fragment = Vertex::mix(a, b, c, u, v, w);
// 				if (depthTest(upTrianglePixelsLeft[i].y, j, fragment) == false) continue;
// 				shader->fragment(fragment, this->target->pixelColor(j, upTrianglePixelsLeft[i].y));
// 			}
// 		}
// 	}
// 	if (tmp_d.x == tmp_c.x)
// 	{
// 		return;
// 	}
// 	downTrianglePixelsLeft = Brasenham(tmp_c, tmp_b);
// 	downTrianglePixelsRight = Brasenham(tmp_c, tmp_d);
// 	for (int i = 0; i < int(downTrianglePixelsLeft.size()); i++)
// 	{
// 		int start, end;
// 		if (i == int(downTrianglePixelsRight.size()))
// 			break;
// 		if (downTrianglePixelsLeft[i].x <= downTrianglePixelsRight[i].x)
// 		{
// 			start = downTrianglePixelsLeft[i].x;
// 			end = downTrianglePixelsRight[i].x;
// 		}
// 		else
// 		{
// 			start = downTrianglePixelsRight[i].x;
// 			end = downTrianglePixelsLeft[i].x;
// 		}
// 		for (int j = start; j < end; j++)
// 		{
// 			Vector4 p(j, downTrianglePixelsLeft[i].y, 0, 1);
// 			u = cross(tmp_b, tmp_c, p) / area;
// 			v = cross(tmp_c, tmp_a, p) / area;
// 			w = 1 - u - v;
// 			Vertex fragment = Vertex::mix(a, b, c, u, v, w);
// 			if (depthTest(downTrianglePixelsLeft[i].y, j, fragment) == false) continue;
// 			shader->fragment(fragment, this->target->pixelColor(j, downTrianglePixelsLeft[i].y));
// 		}
// 	}
// }


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
	float slope1 = (tmp_a.x - tmp_b.x) / (tmp_a.y - tmp_b.y);
	float slope2 = (tmp_a.x - tmp_c.x) / (tmp_a.y - tmp_c.y);

	float tmpX = tmp_a.x;
	float tmpX2 = tmpX;

	float u, v, w, area;
	area = cross(tmp_a, tmp_b, tmp_c);
	if (tmp_a.y != tmp_b.y)
	{
		for (int i = roundFloat(tmp_a.y); i <= roundFloat(tmp_b.y); i++)
		{
			for (int j = min(roundFloat(tmpX), roundFloat(tmpX2)); j <= max(roundFloat(tmpX), roundFloat(tmpX2)); j++)
			{	
				Vector4 p(j, i, 0, 1);
				u = cross(tmp_b, tmp_c, p) / area;
				v = cross(tmp_c, tmp_a, p) / area;
				w = 1 - u - v;
				Vertex fragment = Vertex::mix(a, b, c, u, v, w);
				if (depthTest(i, j, fragment) == false) continue;
				shader->fragment(fragment, this->target->pixelColor(j, i));
			}
			tmpX = tmp_a.x + slope1 * (i + 0.5 - tmp_a.y);
			tmpX2 = tmp_a.x + slope2 * (i + 0.5 - tmp_a.y);
		}
	}

	slope1 = (tmp_c.x - tmp_b.x) / (tmp_c.y - tmp_b.y);
	tmpX = tmp_c.x;
	tmpX2 = tmpX;
	if (tmp_c.y == tmp_b.y)
		return;
	for (int i = roundFloat(tmp_c.y); i >= roundFloat(tmp_b.y); i--)
	{
		for (int j = min(roundFloat(tmpX), roundFloat(tmpX2)); j <= max(roundFloat(tmpX), roundFloat(tmpX2)); j++)
		{
			Vector4 p(j, i, 0, 1);
			u = cross(tmp_b, tmp_c, p) / area;
			v = cross(tmp_c, tmp_a, p) / area;
			w = 1 - u - v;
			Vertex fragment = Vertex::mix(a, b, c, u, v, w);
			if (depthTest(i, j, fragment) == false) continue;
			shader->fragment(fragment, this->target->pixelColor(j, i));
		}
		tmpX = tmp_c.x + slope1 * (i - tmp_c.y);
		tmpX2 = tmp_c.x + slope2 * (i - tmp_c.y);
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
	clip_space.position.x /= clip_space.position.w;
	clip_space.position.y /= clip_space.position.w;
	clip_space.position.z /= clip_space.position.w;
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
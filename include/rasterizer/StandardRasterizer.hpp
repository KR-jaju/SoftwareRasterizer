#ifndef STANDARDRASTERIZER_HPP
#define STANDARDRASTERIZER_HPP

#include "./Rasterizer.hpp"
#include "Clipper.hpp"
#include "Vertex.hpp"
#include "RenderTexture.hpp"
#include "math/fixedPoint.hpp"

class StandardRasterizer : public Rasterizer
{
private:
	int		width;
	int		height;
	RenderTexture	*target;
	void	drawTriangle(Vertex &a, Vertex &b, Vertex &c, Shader *shader);
	void	drawPolygon(std::queue<Vertex> &polygon, Shader *shader);
public:
	StandardRasterizer(int width, int height);
	virtual ~StandardRasterizer();
	bool	depthTest(int y, int x, Vertex &fragment);
	void	draw(Mesh &mesh, int count, Shader *shader, Clipper *clipper);
	void	setTarget(RenderTexture *rt);
	void	blit(int *dst);
};

#endif

#ifndef BARYCENTRIC_RASTERIZER_HPP
# define BARYCENTRIC_RASTERIZER_HPP

# include "Rasterizer.hpp"
# include "Vertex.hpp"

class BarycentricRasterizer : public Rasterizer {
private:
	int		width;
	int		height;
	int		*color;
	float	*depth;
	bool	depthTest(int x, int y, Vertex const &fragment);
	void	drawTriangle(Vertex &a, Vertex &b, Vertex &c, Shader *shader);
public:
	BarycentricRasterizer(int width, int height);
	virtual	~BarycentricRasterizer();
	void	draw(Mesh &mesh, int count, Shader *shader, Clipper *clipper);
	void	blit(int *dst);
};

#endif

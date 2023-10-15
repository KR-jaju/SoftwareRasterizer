
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
	void	drawTriangle(Vertex &a, Vertex &b, Vertex &c);
public:
	BarycentricRasterizer(int width, int height);
	virtual	~BarycentricRasterizer();
	void	draw(Mesh &mesh, int count);
	void	blit(int *dst);
};

#endif

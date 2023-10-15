
#ifndef STANDARD_RASTERIZER_HPP
# define STANDARD_RASTERIZER_HPP

# include "Rasterizer.hpp"
# include "Vertex.hpp"

class StandardRasterizer : public Rasterizer {
private:
	int		width;
	int		height;
	int		*color;
	float	*depth;
	void	drawTriangle(Vertex &a, Vertex &b, Vertex &c);
public:
	StandardRasterizer(int width, int height);
	virtual	~StandardRasterizer();
	void	draw(Mesh &mesh, int count);
	void	blit(int *dst);
};

#endif

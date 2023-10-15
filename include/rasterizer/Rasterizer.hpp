
#ifndef RASTERIZER_HPP
# define RASTERIZER_HPP

# include "Mesh.hpp"

class Rasterizer {
protected:
	Rasterizer() {}
public:
	virtual	~Rasterizer() {};
	virtual void	draw(Mesh &mesh, int count) = 0;
	virtual void	blit(int *dst) = 0;
};

#endif

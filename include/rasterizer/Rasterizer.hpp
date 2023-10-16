
#ifndef RASTERIZER_HPP
# define RASTERIZER_HPP

# include "Mesh.hpp"
# include "Shader.hpp"

class Rasterizer {
protected:
	Rasterizer() {}
public:
	virtual	~Rasterizer() {};
	virtual void	draw(Mesh &mesh, int count, Shader *shader) = 0;
	virtual void	blit(int *dst) = 0;
};

#endif

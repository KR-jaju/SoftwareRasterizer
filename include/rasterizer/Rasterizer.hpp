
#ifndef RASTERIZER_HPP
# define RASTERIZER_HPP

# include "Mesh.hpp"
# include "Shader.hpp"
# include "Clipper.hpp"

class Rasterizer {
protected:
	Rasterizer() {}
public:
	virtual	~Rasterizer() {}
	virtual void	draw(Mesh &mesh, int count, Shader *shader, Clipper *clipper) = 0;
	virtual void	blit(int *dst) = 0;
};

#endif

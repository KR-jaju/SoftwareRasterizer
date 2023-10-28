
#ifndef RASTERIZER_HPP
# define RASTERIZER_HPP

# include "RenderTexture.hpp"
# include "Mesh.hpp"
# include "Shader.hpp"
# include "Clipper.hpp"

class Rasterizer {
protected:
	Rasterizer() {}
public:
	virtual	~Rasterizer() {}
	virtual void	draw(Mesh &mesh, int count, Shader *shader, Clipper *clipper) = 0;
	virtual void	setTarget(RenderTexture *rt) = 0;
	virtual void	blit(int *dst) = 0;
};

enum class DepthFunc {
	NEVER,
	LESS,
	EQUAL,
	LEQUAL,
	GREATER,
	NOT_EQUAL,
	GEQUAL,
	ALWAYS
};

#endif

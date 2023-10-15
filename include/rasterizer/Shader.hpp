
#ifndef SHADER_HPP
# define SHADER_HPP

# include "math/Color.hpp"
# include "rasterizer/Vertex.hpp"

class Shader {
protected:
	Shader() {}
public:
	virtual void	vertex(Vertex &vertex);
	virtual void	fragment(Vertex &in, int &color);
};

#endif

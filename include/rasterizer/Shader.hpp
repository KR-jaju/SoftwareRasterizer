
#ifndef SHADER_HPP
# define SHADER_HPP

# include "math/Color.hpp"
# include "math/Vector4.hpp"
# include "rasterizer/Vertex.hpp"

class Shader {
protected:
	Shader() {}
public:
	virtual void	vertex(Vertex const &in, Vertex &out) = 0;
	virtual void	fragment(Vertex const &in, Vector4 &color) = 0;
};

#endif

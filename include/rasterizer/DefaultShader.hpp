
#ifndef DEFAULT_SHADER_HPP
# define DEFAULT_SHADER_HPP

# include "rasterizer/Shader.hpp"

class DefaultShader : public Shader {
private:

public:
	void	vertex(Vertex const &in, Vertex &out);
	void	fragment(Vertex const &in, int &color);
};

#endif

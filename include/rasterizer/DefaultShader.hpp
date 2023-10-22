
#ifndef DEFAULT_SHADER_HPP
# define DEFAULT_SHADER_HPP

# include "rasterizer/Shader.hpp"
# include "math/Matrix4x4.hpp"

class DefaultShader : public Shader {
private:
	Matrix4x4	view;
	Matrix4x4	projection;
public:
	void	setViewMatrix(Matrix4x4 &m);
	void	setProjectionMatrix(Matrix4x4 &m);
	void	vertex(Vertex const &in, Vertex &out);
	void	fragment(Vertex const &in, Vector4 &color);
};

#endif

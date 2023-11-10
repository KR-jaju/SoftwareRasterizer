
#ifndef RENDER_TEXTURE_HPP
# define RENDER_TEXTURE_HPP

# include "math/Vector4.hpp"

class RenderTexture {
private:
	int		width;
	int		height;
	Vector4	*color;
	_float	*depth;
public:
	RenderTexture(int width, int height);
	~RenderTexture();
	void	clear(Vector4 const &color, _float depth);
	Vector4	&pixelColor(int x, int y);
	_float	&pixelDepth(int x, int y);
};

#endif

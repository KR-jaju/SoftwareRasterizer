
#ifndef RENDER_TEXTURE_HPP
# define RENDER_TEXTURE_HPP

# include "math/Vector4.hpp"

class RenderTexture {
private:
	int		width;
	int		height;
	Vector4	*color;
	float	*depth;
public:
	RenderTexture(int width, int height);
	~RenderTexture();
	void	clear(Vector4 const &color, float depth);
	Vector4	&pixelColor(int x, int y);
	float	&pixelDepth(int x, int y);
};

#endif


#ifndef CLIPPER_HPP
# define CLIPPER_HPP

# include <queue>
# include "rasterizer/Vertex.hpp"

class Clipper {
protected:
	Clipper() {}
public:
	virtual	~Clipper() {}
	virtual void	clip(std::queue<Vertex> &out, Vertex const &a, Vertex const &b, Vertex const &c) = 0;
};

#endif

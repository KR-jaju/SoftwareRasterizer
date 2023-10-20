
#ifndef CLIPPER_HPP
# define CLIPPER_HPP

# include <queue>
# include "rasterizer/Vertex.hpp"

class Clipper {
public:
	Clipper() {}
	~Clipper() {}
	void	clip(std::queue<Vertex> &out);
};

#endif


#ifndef WEILER_ATHERTON_CLIPPER_HPP
# define WEILER_ATHERTON_CLIPPER_HPP

# include "./Clipper.hpp"

class WeilerAthertonClipper: public Clipper {
	~WeilerAthertonClipper();
	void	clip(std::queue<Vertex> &out, Vertex const &a, Vertex const &b, Vertex const &c);
};

#endif

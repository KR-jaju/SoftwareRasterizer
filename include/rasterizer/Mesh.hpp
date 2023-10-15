
#ifndef MESH_HPP
# define MESH_HPP

# include "rasterizer/Vertex.hpp"

class Mesh {
private:
	Vertex	*vertices;
	int		size;
public:
	Mesh(int size);
	int		getSize();
	Vertex	&get(int idx);
	Vertex	&operator[](int idx);
};

#endif
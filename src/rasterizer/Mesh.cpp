
#include "rasterizer/Mesh.hpp"

Mesh::Mesh(int size) {
	this->vertices = new Vertex[size];
	this->size = size;
}

Vertex	&Mesh::get(int idx) {
	return (this->vertices[idx]);
}


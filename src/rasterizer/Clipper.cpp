
#include "rasterizer/Clipper.hpp"

static
bool	isInside(Vertex const &vertex, Vector4 const &axis) {
	_float const	w = vertex.position.w;
	_float const	v = vertex.position * axis;

	return (v <= w);
}

static
Vertex	boundary(Vertex const &a, Vertex const &b, Vector4 const &axis) {
	_float const	a0 = a.position * axis;
	_float const	b0 = b.position * axis;
	_float const diff_a = a0 - a.position.w;
	_float const diff_b = b0 - b.position.w;
	_float const	t = diff_a / (diff_a - diff_b);
	return Vertex::mix(a, b, t);
}

static
void	clipPlane(std::queue<Vertex> &queue, Vector4 const &axis) {
	int const	count = static_cast<int>(queue.size());
	Vertex		curr;
	Vertex		next;

	if (count <= 2)
		return ;
	next = queue.front();
	queue.pop();
	queue.push(next);
	for (int i = 0; i < count; i++) {
		curr = next;
		next = queue.front();
		queue.pop();
		Vertex intersection = boundary(curr, next, axis);
		if (isInside(next, axis)) {
			if (!isInside(curr, axis)) {
				queue.push(intersection);
			}
			queue.push(next);
		}
		else if (isInside(curr, axis)) {
			queue.push(intersection);
		}
	}
}

void	Clipper::clip(std::queue<Vertex> &out) {
	clipPlane(out, Vector4(1, 0, 0, 0));
	clipPlane(out, Vector4(-1, 0, 0, 0));
	clipPlane(out, Vector4(0, 1, 0, 0));
	clipPlane(out, Vector4(0, -1, 0, 0));
	clipPlane(out, Vector4(0, 0, 1, 0));
	clipPlane(out, Vector4(0, 0, -1, 0));
}
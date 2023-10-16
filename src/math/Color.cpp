
#include "math/Color.hpp"
#include <cmath>

Color::Color(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::operator	int() const {
	int const	r = static_cast<int>(roundf(this->r * 255)) & 0xff;
	int const	g = static_cast<int>(roundf(this->g * 255)) & 0xff;
	int const	b = static_cast<int>(roundf(this->b * 255)) & 0xff;
	int const	a = static_cast<int>(roundf(this->a * 255)) & 0xff;
	return (a << 24 | r << 16 | g << 8 | b);
}



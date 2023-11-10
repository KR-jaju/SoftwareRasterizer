
#include "math/Color.hpp"
#include <cmath>

Color::Color(_float r, _float g, _float b, _float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::operator	int() {
	int const	r = static_cast<int>((this->r * 255).round().getReal()) & 0xff;
	int const	g = static_cast<int>((this->g * 255).round().getReal()) & 0xff;
	int const	b = static_cast<int>((this->b * 255).round().getReal()) & 0xff;
	int const	a = static_cast<int>((this->a * 255).round().getReal()) & 0xff;
	return (a << 24 | r << 16 | g << 8 | b);
}

Color	Color::operator+(const Color &ref) const {
	return Color(this->r + ref.r,
				this->g + ref.g,
				this->b + ref.b,
				this->a + ref.a);
}

Color	Color::operator-(const Color &ref) const{
	return Color(this->r - ref.r,
				this->g - ref.g,
				this->b - ref.b,
				this->a - ref.a);
}

Color	Color::operator-() const {
	return Color(this->r * -1, this->g * -1, this->b * -1, this->a * -1);
}

Color	Color::operator*(_float f) const {
	return Color(this->r * f,
				this->g * f,
				this->b * f,
				this->a * f);
}

Color	Color::operator*(const Color &ref) const {
	return Color(this->r * ref.r,
				this->g * ref.g,
				this->b * ref.b,
				this->a * ref.a);
}
Color	Color::operator/(_float f) const {
	return Color(this->r / f,
				this->g / f,
				this->b / f,
				this->a / f);
}



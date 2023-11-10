
#ifndef COLOR_HPP
# define COLOR_HPP

#include "fixedPoint.hpp"

struct Color {
	_float	r;
	_float	g;
	_float	b;
	_float	a;
	Color() {}
	Color(_float r, _float g, _float b, _float a);
	operator	int();
	Color	operator+(const Color &ref) const;
	Color	operator-(const Color &ref) const;
	Color	operator-() const;
	Color	operator*(_float f) const;
	Color	operator*(const Color &ref) const;
	Color	operator/(_float f) const;
};


#endif

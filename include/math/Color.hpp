
#ifndef COLOR_HPP
# define COLOR_HPP

struct Color {
	float	r;
	float	g;
	float	b;
	float	a;
	Color() {}
	Color(float r, float g, float b, float a);
	operator	int() const;
	Color	operator+(const Color &ref) const;
	Color	operator-(const Color &ref) const;
	Color	operator-() const;
	Color	operator*(float f) const;
	Color	operator*(const Color &ref) const;
	Color	operator/(float f) const;
};


#endif

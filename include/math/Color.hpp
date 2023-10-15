
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
};


#endif

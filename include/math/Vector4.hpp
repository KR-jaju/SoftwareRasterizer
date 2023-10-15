
#ifndef VECTOR4_HPP
# define VECTOR4_HPP

struct Vector4 {
	float	x;
	float	y;
	float	z;
	float	w;
	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(const Vector4 &ref);
	Vector4& operator=(const Vector4 &ref);
};

#endif

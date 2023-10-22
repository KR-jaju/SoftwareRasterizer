
#ifndef VECTOR4_HPP
# define VECTOR4_HPP

# include "Color.hpp"
# include "Vector3.hpp"

struct Vector4 {
	float	x;
	float	y;
	float	z;
	float	w;
	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(Vector3 const &v, float w);
	Vector4(const Vector4 &ref);
	Vector4	&operator=(const Vector4 &ref);
	Vector4	operator+(const Vector4 &ref) const;
	Vector4	operator-(const Vector4 &ref) const;
	Vector4	operator-() const;
	Vector4	operator*(float f) const;
	float	operator*(const Vector4 &ref) const;
	Vector4	operator/(float f) const;
	operator	Color() const;
	float	lengthSqr() const;
	float	length() const;
	Vector4	normalized() const;
};

#endif

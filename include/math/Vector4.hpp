
#ifndef VECTOR4_HPP
# define VECTOR4_HPP

# include "Color.hpp"
# include "Vector3.hpp"

struct Vector4 {
	_float	x;
	_float	y;
	_float	z;
	_float	w;
	Vector4();
	Vector4(_float x, _float y, _float z, _float w);
	Vector4(Vector3 const &v, _float w);
	Vector4(const Vector4 &ref);
	Vector4	&operator=(const Vector4 &ref);
	Vector4	operator+(const Vector4 &ref) const;
	Vector4	operator-(const Vector4 &ref) const;
	Vector4	operator-() const;
	Vector4	operator*(_float f) const;
	_float	operator*(const Vector4 &ref) const;
	Vector4	operator/(_float f) const;
	operator	Color() const;
	_float	lengthSqr() const;
	_float	length() const;
	Vector4	normalized() const;
};

#endif

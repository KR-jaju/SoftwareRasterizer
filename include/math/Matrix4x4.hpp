#ifndef MATRIX4X4_HPP
# define MATRIX4X4_HPP

# include "Vector4.hpp"

struct Matrix4x4 {
	_float	m[4][4];
	Matrix4x4() {}
	Matrix4x4(const Matrix4x4 &ref);
	Matrix4x4& operator=(const Matrix4x4 &ref);
	_float	&operator[](int idx);
	Matrix4x4	operator*(Matrix4x4 const &m);
	Vector4		operator*(Vector4 const &v);
};

#endif
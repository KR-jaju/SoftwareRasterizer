#pragma once
#include "Vector4.h"

struct Matrix4x4 {
	float	m[4][4];

	static Matrix4x4 createIdentity();
	static Matrix4x4 createScale(float x, float y, float z);
	static Matrix4x4 createRotation(float yaw, float pitch, float roll);
	static Matrix4x4 createTranslation(float x, float y, float z);

	Matrix4x4() = default;
	Matrix4x4(const Matrix4x4 &ref);
	Matrix4x4& operator=(const Matrix4x4 &ref);
	float	&operator[](int idx);
	Matrix4x4	operator*(Matrix4x4 const &m);
	Vector4		operator*(Vector4 const &v);
	Matrix4x4	transpose() const;
};

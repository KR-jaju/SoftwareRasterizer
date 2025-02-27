#pragma once
#include "Vector3.h"

struct Quaternion {
	float	w;
	float	x;
	float	y;
	float	z;

	static Quaternion createFromAxisAngle(Vector3 const& axis, float angle);

	Quaternion(float w, float x, float y, float z);
	Quaternion	operator+(Quaternion const &q) const;
	Quaternion	operator-(Quaternion const &q) const;
	Quaternion	operator*(float f) const;
	Quaternion	operator*(Quaternion const &q) const;
	Vector3		operator*(Vector3 const &v) const;
	Quaternion	operator/(float f) const;
	Quaternion	operator~() const;
	Quaternion	inverse() const;
	operator	Vector3() const;

	float	sqrMagnitude() const;
	float	magnitude() const;
};

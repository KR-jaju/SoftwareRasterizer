
#ifndef QUATERNION_HPP
# define QUATERNION_HPP

# include "Vector3.hpp"

struct Quaternion {
	_float	w;
	_float	x;
	_float	y;
	_float	z;
	Quaternion(_float w, _float x, _float y, _float z);
	Quaternion	operator+(Quaternion const &q) const;
	Quaternion	operator-(Quaternion const &q) const;
	Quaternion	operator*(_float f) const;
	Quaternion	operator*(Quaternion const &q) const;
	Vector3		operator*(Vector3 const &v) const;
	Quaternion	operator/(_float f) const;
	Quaternion	operator~() const;
	Quaternion	inverse() const;
	operator	Vector3() const;

	_float	sqrMagnitude() const;
	_float	magnitude() const;
};

#endif

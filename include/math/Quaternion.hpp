
#ifndef QUATERNION_HPP
# define QUATERNION_HPP

struct Quaternion {
	float	w;
	float	x;
	float	y;
	float	z;
	Quaternion(float w, float x, float y, float z);
	Quaternion	operator+(Quaternion const &q) const;
	Quaternion	operator-(Quaternion const &q) const;
	Quaternion	operator*(float f) const;
	Quaternion	operator*(Quaternion const &q) const;
	Quaternion	operator/(float f) const;
	Quaternion	operator~() const;
	Quaternion	inverse() const;

	float	sqrMagnitude() const;
	float	magnitude() const;
};

#endif

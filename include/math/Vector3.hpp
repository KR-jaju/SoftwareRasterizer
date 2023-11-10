
#ifndef VECTOR3_HPP
# define VECTOR3_HPP

# include "./Color.hpp"
# include "./fixedPoint.hpp"

struct Vector3 {
	_float	x;
	_float	y;
	_float	z;
public:
	Vector3();
	Vector3(_float x, _float y, _float z);
	Vector3(const Vector3 &ref);
	Vector3	&operator=(const Vector3 &ref);
	Vector3	operator+(const Vector3 &ref) const;
	Vector3	operator-(const Vector3 &ref) const;
	Vector3	operator-() const;
	Vector3	operator*(_float f) const;
	_float	operator*(const Vector3 &ref) const;
	Vector3	operator/(_float f) const;
	Vector3	cross(Vector3 const &ref) const;
	_float	lengthSqr() const;
	_float	length() const;
	Vector3	normalized() const;
	operator	Color() const;
};

#endif

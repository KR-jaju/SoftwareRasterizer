
#ifndef VECTOR3_HPP
# define VECTOR3_HPP

struct Vector3 {
	float	x;
	float	y;
	float	z;
public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3 &ref);
	Vector3	&operator=(const Vector3 &ref);
	Vector3	operator+(const Vector3 &ref) const;
	Vector3	operator-(const Vector3 &ref) const;
	Vector3	operator-() const;
	Vector3	operator*(float f) const;
	float	operator*(const Vector3 &ref) const;
	Vector3	operator/(float f) const;
	Vector3	cross(Vector3 const &ref) const;
	float	lengthSqr() const;
	float	length() const;
	Vector3	normalized() const;
};

#endif

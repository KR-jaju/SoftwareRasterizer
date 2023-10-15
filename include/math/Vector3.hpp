
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
	Vector3& operator=(const Vector3 &ref);
};

#endif

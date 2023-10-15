
#ifndef VECTOR3_HPP
# define VECTOR3_HPP

struct Vector3 {
	float	x;
	float	y;
	float	z;
public:
	Vector3() {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3(const Vector3 &ref) { this->x = ref.x; this->y = ref.y; this->z=ref.z; }
	Vector3& operator=(const Vector3 &ref) { this->x = ref.x; this->y = ref.y; this->z=ref.z; return *this; }
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	void setZ(float z) { this->z = z; }
};

#endif

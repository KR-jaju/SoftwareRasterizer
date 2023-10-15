
#ifndef VECTOR4_HPP
# define VECTOR4_HPP

struct Vector4 {
	float	x;
	float	y;
	float	z;
public:
	Vector4() {}
	Vector4(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector4(const Vector4 &ref) { this->x = ref.x; this->y = ref.y; this->z=ref.z; }
	Vector4& operator=(const Vector4 &ref) {
		this->x = ref.x;
		this->y = ref.y;
		this->z = ref.z;
		return (*this);
	}
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	void setZ(float z) { this->z = z; }
};

#endif

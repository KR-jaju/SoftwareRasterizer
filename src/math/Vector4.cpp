
#include "math/Vector4.hpp"

Vector4::Vector4() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(const Vector4 &ref) {
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
	this->w = ref.w;
}

Vector4& Vector4::operator=(const Vector4 &ref) {
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
	this->w = ref.w;
	return *this;
}

float	Vector4::dot(Vector4 const &ref) {
	return (ref.x * this->x + ref.y * this->y + ref.z * this->z + ref.w * this->w);
}

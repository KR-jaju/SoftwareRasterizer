
#include "math/Vector3.hpp"

Vector3::Vector3() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(const Vector3 &ref) {
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
}

Vector3& Vector3::operator=(const Vector3 &ref) {
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
	return *this;
}

float Vector3::getX() { return x; }
	float Vector3::getY() { return y; }
	float Vector3::getZ() { return z; }
	void Vector3::setX(float x) { this->x = x; }
	void Vector3::setY(float y) { this->y = y; }
	void Vector3::setZ(float z) { this->z = z; }


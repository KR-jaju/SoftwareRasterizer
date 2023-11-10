#include "math/Vector3.hpp"
#include <cmath>

Vector3::Vector3() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(_float x, _float y, _float z) {
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

Vector3	Vector3::operator+(const Vector3 &ref) const {
	Vector3	ret;

	ret.x = this->x + ref.x;
	ret.y = this->y + ref.y;
	ret.z = this->z + ref.z;
	return (ret);
}

Vector3	Vector3::operator-(const Vector3 &ref) const {
	Vector3	ret;

	ret.x = this->x - ref.x;
	ret.y = this->y - ref.y;
	ret.z = this->z - ref.z;
	return (ret);
}

Vector3	Vector3::operator-() const {
	return (Vector3(-this->x, -this->y, -this->z));
}

Vector3	Vector3::operator*(_float f) const {
	Vector3	ret;

	ret.x = this->x * f;
	ret.y = this->y * f;
	ret.z = this->z * f;
	return (ret);
}

_float	Vector3::operator*(const Vector3 &ref) const {
	return (this->x * ref.x + this->y * ref.y + this->z * ref.z);
}

Vector3	Vector3::operator/(_float f) const {
	Vector3	ret;

	ret.x = this->x / f;
	ret.y = this->y / f;
	ret.z = this->z / f;
	return (ret);
}

Vector3	Vector3::cross(Vector3 const &ref) const {
	Vector3	ret;

	ret.x = this->y * ref.z - this->z * ref.y;
	ret.y = this->z * ref.x - this->x * ref.z;
	ret.z = this->x * ref.y - this->y * ref.x;
	return (ret);
}

_float	Vector3::lengthSqr() const {
	return (*this * *this);
}

_float	Vector3::length() const {
	return ((this->lengthSqr()).sqrt());
}

Vector3	Vector3::normalized() const {
	Vector3	ret(*this);

	return (ret / ret.length());
}

Vector3::operator Color() const {
	return (Color (this->x, this->y, this->z, 0));
}


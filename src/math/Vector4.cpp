
#include "math/Vector4.hpp"
#include <cmath>

Vector4::Vector4() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

Vector4::Vector4(_float x, _float y, _float z, _float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(Vector3 const &v, _float w) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = w;
}

Vector4::Vector4(const Vector4 &ref) {
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
	this->w = ref.w;
}

Vector4	&Vector4::operator=(const Vector4 &ref) {
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
	this->w = ref.w;
	return *this;
}

Vector4	Vector4::operator+(const Vector4 &ref) const {
	Vector4	ret;

	ret.x = this->x + ref.x;
	ret.y = this->y + ref.y;
	ret.z = this->z + ref.z;
	ret.w = this->w + ref.w;
	return (ret);
}

Vector4	Vector4::operator-(const Vector4 &ref) const {
	Vector4	ret;

	ret.x = this->x - ref.x;
	ret.y = this->y - ref.y;
	ret.z = this->z - ref.z;
	ret.w = this->w - ref.w;
	return (ret);
}

Vector4	Vector4::operator-() const {
	Vector4	ret;

	ret.x = -this->x;
	ret.y = -this->y;
	ret.z = -this->z;
	ret.w = -this->w;
	return (ret);
}

Vector4	Vector4::operator*(_float f) const {
	Vector4	ret;

	ret.x = this->x * f;
	ret.y = this->y * f;
	ret.z = this->z * f;
	ret.w = this->w * f;
	return (ret);
}

_float	Vector4::operator*(const Vector4 &ref) const {
	return (ref.x * this->x + ref.y * this->y + ref.z * this->z + ref.w * this->w);
}

Vector4	Vector4::operator/(_float f) const {
	Vector4	ret;

	ret.x = this->x / f;
	ret.y = this->y / f;
	ret.z = this->z / f;
	ret.w = this->w / f;
	return (ret);
}

Vector4::operator	Color() const {
	return (Color(this->x, this->y, this->z, this->w));
}

_float	Vector4::lengthSqr() const {
	return (*this * *this);
}

_float	Vector4::length() const {
	return ((this->lengthSqr()).sqrt());
}

Vector4	Vector4::normalized() const {
	return (*this / this->length());
}

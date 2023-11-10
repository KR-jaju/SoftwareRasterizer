
#include "math/Quaternion.hpp"
#include <cmath>

Quaternion::Quaternion(_float w, _float x, _float y, _float z) {
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

Quaternion	Quaternion::operator+(Quaternion const &q) const {
	return (Quaternion(
		this->w + q.w,
		this->x + q.x,
		this->y + q.y,
		this->z + q.z
	));
}

Quaternion	Quaternion::operator-(Quaternion const &q) const{
	return (Quaternion(
		this->w - q.w,
		this->x - q.x,
		this->y - q.y,
		this->z - q.z
	));
}

Quaternion	Quaternion::operator*(_float f) const {
		return (Quaternion(
		this->w * f,
		this->x * f,
		this->y * f,
		this->z * f
	));
}

Quaternion	Quaternion::operator/(_float f) const {
		return (Quaternion(
		this->w / f,
		this->x / f,
		this->y / f,
		this->z / f
	));
}

Quaternion	Quaternion::operator*(Quaternion const &q) const{
	Quaternion	ret(0, 0, 0, 0);

	ret.w = this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z;
	ret.x = this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y;
	ret.y = this->w * q.y - this->x * q.z + this->y * q.w + this->z * q.x;
	ret.z = this->w * q.z + this->x * q.y - this->y * q.x + this->z * q.w;
	return (ret);
}

Vector3	Quaternion::operator*(Vector3 const &v) const {
	Quaternion	q(0, v.x, v.y, v.z);

	return *this * q * ~*this;
}

Quaternion	Quaternion::operator~() const {
	return (Quaternion(this->w, -this->x, -this->y, -this->z));
}

Quaternion	Quaternion::inverse() const {
	return (~*this / this->sqrMagnitude());
}

Quaternion::operator	Vector3() const {
	return (Vector3(this->x, this->y, this->z));
}

_float	Quaternion::sqrMagnitude() const {
	return (this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

_float	Quaternion::magnitude() const {
	return ((this->sqrMagnitude()).sqrt());
}
#include "math/Matrix4x4.hpp"


Matrix4x4::Matrix4x4(const Matrix4x4 &ref) {
	*this = ref;
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4 &ref) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->m[i][j] = ref.m[i][j];
	return (*this);
}

_float	&Matrix4x4::operator[](int idx) {
	return (this->m[idx / 4][idx % 4]);
}

Matrix4x4	Matrix4x4::operator*(Matrix4x4 const &m) {
	Matrix4x4	ret;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			ret.m[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				ret.m[i][j] += this->m[i][k] * m.m[k][j];
			}
		}
	}
	return (ret);
}

Vector4	Matrix4x4::operator*(Vector4 const &v) {
	Vector4	ret;

	ret.x = this->m[0][0] * v.x + this->m[0][1] * v.y + this->m[0][2] * v.z + this->m[0][3] * v.w;
	ret.y = this->m[1][0] * v.x + this->m[1][1] * v.y + this->m[1][2] * v.z + this->m[1][3] * v.w;
	ret.z = this->m[2][0] * v.x + this->m[2][1] * v.y + this->m[2][2] * v.z + this->m[2][3] * v.w;
	ret.w = this->m[3][0] * v.x + this->m[3][1] * v.y + this->m[3][2] * v.z + this->m[3][3] * v.w;
	return (ret);
}

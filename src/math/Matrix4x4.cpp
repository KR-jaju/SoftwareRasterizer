#include "math/Matrix4x4.h"
#include <cmath>

Matrix4x4 Matrix4x4::createIdentity()
{
	Matrix4x4 result;

	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			result.m[r][c] = ((r == c) ? 1 : 0);
		}
	}
	return (result);
}

Matrix4x4 Matrix4x4::createScale(float x, float y, float z)
{
	Matrix4x4 result;
	
	result.m[0][0] = x;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	
	result.m[1][0] = 0;
	result.m[1][1] = y;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = z;
	result.m[2][3] = 0;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;
	return (result);
}

Matrix4x4 Matrix4x4::createRotation(float yaw, float pitch, float roll)
{
    Matrix4x4 result;
    
    float cy = std::cos(yaw);
    float sy = std::sin(yaw);
    float cp = std::cos(pitch);
    float sp = std::sin(pitch);
    float cr = std::cos(roll);
    float sr = std::sin(roll);
    
    result.m[0][0] = cy * cr + sy * sp * sr;
    result.m[0][1] = -cy * sr + sy * sp * cr;
    result.m[0][2] = sy * cp;
    result.m[0][3] = 0.0f;
    
    result.m[1][0] = cp * sr;
    result.m[1][1] = cp * cr;
    result.m[1][2] = -sp;
    result.m[1][3] = 0.0f;
    
    result.m[2][0] = -sy * cr + cy * sp * sr;
    result.m[2][1] = sy * sr + cy * sp * cr;
    result.m[2][2] = cy * cp;
    result.m[2][3] = 0.0f;
    
    result.m[3][0] = 0.0f;
    result.m[3][1] = 0.0f;
    result.m[3][2] = 0.0f;
    result.m[3][3] = 1.0f;
    
    return result;
}

Matrix4x4 Matrix4x4::createTranslation(float x, float y, float z)
{
	Matrix4x4 result;
	
	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = x;
	
	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = y;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = z;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;
	return (result);
}



Matrix4x4::Matrix4x4(const Matrix4x4 &ref) {
	*this = ref;
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4 &ref) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->m[i][j] = ref.m[i][j];
	return (*this);
}

float	&Matrix4x4::operator[](int idx) {
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


Matrix4x4	Matrix4x4::transpose() const
{
    Matrix4x4 result;

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result.m[i][j] = m[j][i];
        }
    }
    return (result);
}

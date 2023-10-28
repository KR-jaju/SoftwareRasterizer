
#include "util/MatrixUtil.hpp"
#include <cmath>

void	MatrixUtil::identity(Matrix4x4 &mat) {
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			if (r == c)
				mat.m[r][c] = 1;
			else
				mat.m[r][c] = 0;
		}
	}
}

void	MatrixUtil::scaleMatrix(Matrix4x4 &mat, Vector3 const &scale) {
	for (int r = 0; r < 3; r++) {
		mat.m[r][0] *= scale.x;
		mat.m[r][1] *= scale.y;
		mat.m[r][2] *= scale.z;
	}
}

void	MatrixUtil::rotateMatrix(Matrix4x4 &mat, Quaternion const &rotation) {
	for (int c = 0; c < 3; c++) {
		Vector3 const	row = rotation * Vector3(mat.m[0][c], mat.m[1][c], mat.m[2][c]);

		mat.m[0][c] = row.x;
		mat.m[1][c] = row.y;
		mat.m[2][c] = row.z;
	}
}

void	MatrixUtil::translateMatrix(Matrix4x4 &mat, Vector3 const &translation) {
	mat.m[0][3] += translation.x;
	mat.m[1][3] += translation.y;
	mat.m[2][3] += translation.z;
}

void	MatrixUtil::viewMatrix(Matrix4x4 &ref, Vector3 const &pos, Vector3 const &dir) {
	Vector3	forward = dir.normalized();
	Vector3	right = Vector3(0, 1, 0).cross(forward).normalized();
	Vector3 up = forward.cross(right);

	ref.m[0][0] = right.x;
	ref.m[0][1] = right.y;
	ref.m[0][2] = right.z;
	ref.m[0][3] = -pos * right;
	ref.m[1][0] = up.x;
	ref.m[1][1] = up.y;
	ref.m[1][2] = up.z;
	ref.m[1][3] = -pos * up;
	ref.m[2][0] = forward.x;
	ref.m[2][1] = forward.y;
	ref.m[2][2] = forward.z;
	ref.m[2][3] = -pos * forward;
	ref.m[3][0] = 0;
	ref.m[3][1] = 0;
	ref.m[3][2] = 0;
	ref.m[3][3] = 1;
}

void	MatrixUtil::tmpModelMatrix(Matrix4x4 &m, float degree)
{
	float radi = degree * M_PI / 180.0;
	m.m[0][0] = cosf(radi);
	m.m[0][1] = -sinf(radi);
	m.m[0][2] = 0;
	m.m[0][3] = 0;

	m.m[1][0] = sinf(radi);
	m.m[1][1] = cosf(radi);
	m.m[1][2] = 0;
	m.m[1][3] = 0;

	m.m[2][0] = 0;
	m.m[2][1] = 0;
	m.m[2][2] = 1;
	m.m[2][3] = 0;

	m.m[3][0] = 0;
	m.m[3][1] = 0;
	m.m[3][2] = 0;
	m.m[3][3] = 1;
}

void	MatrixUtil::modelMatrix(Matrix4x4 &m, Vector3 const &translation, Quaternion const &rotation, Vector3 const &scale) {
	MatrixUtil::identity(m);
	MatrixUtil::scaleMatrix(m, scale);
	MatrixUtil::rotateMatrix(m, rotation);
	MatrixUtil::translateMatrix(m, translation);
}

void	MatrixUtil::perspectiveMatrix(Matrix4x4 &ref, float fov, float aspect, float near, float far) {
	float const	t = 1 / tanf(fov / 360 * M_PI);

	ref.m[0][0] = t;
	ref.m[0][1] = 0;
	ref.m[0][2] = 0;
	ref.m[0][3] = 0;
	ref.m[1][0] = 0;
	ref.m[1][1] = t * aspect;
	ref.m[1][2] = 0;
	ref.m[1][3] = 0;
	ref.m[2][0] = 0;
	ref.m[2][1] = 0;
	ref.m[2][2] = -(near + far) / (near - far);
	ref.m[2][3] = 2 * near * far / (near - far);
	ref.m[3][0] = 0;
	ref.m[3][1] = 0;
	ref.m[3][2] = 1;
	ref.m[3][3] = 0;
}


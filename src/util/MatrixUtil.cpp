
#include "util/MatrixUtil.hpp"
#include <cmath>

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

// void	MatrixUtil::modelMatrix(Matrix4x4 &m, Vector3 ) {
	
// }

void	MatrixUtil::perspectiveMatrix(Matrix4x4 &ref, float fov, float aspect, float near, float far) {
	float	t = 1 / tanf(fov / 360 * M_PI);
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


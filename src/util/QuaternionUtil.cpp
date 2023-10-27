
#include "util/QuaternionUtil.hpp"
#include <cmath>

Quaternion	QuaternionUtil::rotation(Vector3 axis, float angle) {
	float const	c = cosf(angle / 180 * M_PI);
	float const	s = sinf(angle / 180 * M_PI);

	return(Quaternion(c, axis.x * s, axis.y * s, axis.z * s));
}
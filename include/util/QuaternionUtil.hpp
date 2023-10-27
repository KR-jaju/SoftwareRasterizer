#ifndef QUATERNION_UTIL_HPP
# define QUATERNION_UTIL_HPP

# include "math/Quaternion.hpp"
# include "math/Vector3.hpp"

class QuaternionUtil
{
private:
	QuaternionUtil();
public:
	static Quaternion	rotation(Vector3 axis, float angle);
};



#endif
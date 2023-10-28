
#ifndef MATRIX_UTIL_HPP
# define MATRIX_UTIL_HPP

# include "math/Matrix4x4.hpp"
# include "math/Quaternion.hpp"
# include "math/Vector3.hpp"

class MatrixUtil
{
private:
	MatrixUtil();
public:
	static void	identity(Matrix4x4 &m);
	static void	scaleMatrix(Matrix4x4 &m, Vector3 const &scale);
	static void	rotateMatrix(Matrix4x4 &m, Quaternion const &rotation);
	static void	translateMatrix(Matrix4x4 &m, Vector3 const &translation);
	static void	viewMatrix(Matrix4x4 &m, Vector3 const &pos, Vector3 const &dir);
	static void	tmpModelMatrix(Matrix4x4 &m, float degree);
	static void	modelMatrix(Matrix4x4 &m, Vector3 const &translation, Quaternion const &rotation, Vector3 const &scale);
	static void	perspectiveMatrix(Matrix4x4 &m, float fov, float aspect, float near, float far);
};



#endif

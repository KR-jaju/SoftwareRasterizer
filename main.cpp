extern "C" {
	#include "mlx/mlx.h"
}
#include "rasterizer/BarycentricRasterizer.hpp"
#include "rasterizer/StandardRasterizer.hpp"
#include "rasterizer/DefaultShader.hpp"
#include "rasterizer/WeilerAthertonClipper.hpp"
#include "util/MatrixUtil.hpp"

int	main(void) {
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	if (mlx == (void *)0)
		return (1);
	window = mlx_new_window(mlx, 512, 512, const_cast<char *>("Raycaster"));
	void	*image = mlx_new_image(mlx, 512, 512);
	int		a;
	int		*data = (int *)mlx_get_data_addr(image, &a, &a, &a);

	Matrix4x4		view;
	Matrix4x4		projection;
	DefaultShader	shader;

	MatrixUtil::viewMatrix(view, Vector3(0, 0, 0), Vector3(0, 0, 1));
	MatrixUtil::perspectiveMatrix(projection, 90, 1, 0.3, 1000.0);
	shader.setViewMatrix(view);
	shader.setProjectionMatrix(projection);

	Mesh mesh(3);

	mesh.get(0).position = Vector4(-1, 0, 1, 1);
	mesh.get(1).position = Vector4(0, 1, 1, 1);
	mesh.get(2).position = Vector4(0.8, -0.5, 1, 1);
	mesh.get(0).normal = Vector3(1.0, 0.0, 0.0);
	mesh.get(1).normal = Vector3(0.0, 1.0, 0.0);
	mesh.get(2).normal = Vector3(0.0, 0.0, 1.0);
	// Rasterizer	*rasterizer = new StandardRasterizer(512, 512);
	Rasterizer	*rasterizer = new BarycentricRasterizer(512, 512);
	Clipper		*clipper = new WeilerAthertonClipper();
	rasterizer->draw(mesh, 3, &shader, clipper);
	rasterizer->blit(data);
	mlx_put_image_to_window(mlx, window, image, 0, 0);
	mlx_loop(mlx);
	return (0);
}




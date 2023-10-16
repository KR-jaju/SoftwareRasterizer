extern "C" {
	#include "mlx/mlx.h"
}
#include "rasterizer/BarycentricRasterizer.hpp"
#include "rasterizer/StandardRasterizer.hpp"
#include "rasterizer/DefaultShader.hpp"

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


	DefaultShader	shader;


	Mesh mesh(3);

	mesh.get(0).position = Vector3(-1, 0, 0);
	mesh.get(1).position = Vector3(0, 1, 0);
	mesh.get(2).position = Vector3(0.8, -0.2, 0);
	// Rasterizer	*rasterizer = new StandardRasterizer(512, 512);
	Rasterizer	*rasterizer = new BarycentricRasterizer(512, 512);
	rasterizer->draw(mesh, 3, &shader);
	rasterizer->blit(data);
	mlx_put_image_to_window(mlx, window, image, 0, 0);
	mlx_loop(mlx);
	return (0);
}




extern "C" {
	#include "mlx/mlx.h"
}
#include "rasterizer/BarycentricRasterizer.hpp"
#include "rasterizer/StandardRasterizer.hpp"
#include "rasterizer/DefaultShader.hpp"
#include "rasterizer/CohenSutherlandClipper.hpp"
#include "util/MatrixUtil.hpp"
#include <stdlib.h>
#include <fcntl.h>

int	exit_hook(void)
{
	exit(0);
}

typedef struct vars
{
	void	*mlx;
	void	*window;
	void	*image;
	int		tmp;
	int		*data;
}	t_vars;


int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->window);
		exit(0);
	}
	return (0);
}

int	main(void) {
	t_vars	vars;

	vars.mlx = mlx_init();
	if (vars.mlx == (void *)0)
		return (1);
	vars.window = mlx_new_window(vars.mlx, 512, 512, const_cast<char *>("Raycaster"));
	vars.image = mlx_new_image(vars.mlx, 512, 512);
	vars.data = (int *)mlx_get_data_addr(vars.image, &(vars.tmp), &(vars.tmp), &(vars.tmp));

	Matrix4x4		view;
	Matrix4x4		projection;
	DefaultShader	shader;

	MatrixUtil::viewMatrix(view, Vector3(0, 0, -0.5), Vector3(0, 0, 1));
	MatrixUtil::perspectiveMatrix(projection, 90, 1, 0.3, 1000.0);
	shader.setViewMatrix(view);
	shader.setProjectionMatrix(projection);

	Mesh mesh(3);

	mesh.get(0).position = Vector4(-1, 0, 1, 1);
	mesh.get(1).position = Vector4(0, 0.2, -0.4, 1);
	mesh.get(2).position = Vector4(0.8, -0.5, 1, 1);
	mesh.get(0).normal = Vector3(1.0, 0.0, 0.0);
	mesh.get(1).normal = Vector3(0.0, 1.0, 0.0);
	mesh.get(2).normal = Vector3(0.0, 0.0, 1.0);
	Rasterizer	*rasterizer = new StandardRasterizer(512, 512);
	RenderTexture	rt(512, 512);
	rt.clear(Vector4(0, 0, 0, 0), 1.0f);
	// Rasterizer	*rasterizer = new BarycentricRasterizer(512, 512);
	rasterizer->setTarget(&rt);
	// Clipper		*clipper = new Clipper();
	Clipper		*clipper = new CohenSutherandClipper();
	rasterizer->draw(mesh, 3, &shader, clipper);
	rasterizer->blit(vars.data);
	mlx_put_image_to_window(vars.mlx, vars.window, vars.image, 0, 0);
	typedef int (*funct_ptr)();
	mlx_key_hook(vars.window, reinterpret_cast<funct_ptr>(key_hook), &vars);
	mlx_hook(vars.window, 17, 0, exit_hook, 0);
	mlx_loop(vars.mlx);
	return (0);
}



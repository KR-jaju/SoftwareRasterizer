extern "C" {
	#include "mlx/mlx.h"
}

int	main(void) {
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	if (mlx == (void *)0)
		return (1);
	window = mlx_new_window(mlx, 512, 512, const_cast<char *>("Raycaster"));
	(void) window;
	mlx_loop(mlx);
	return (0);
}




#include "srcs/cub3d.h"
#include "mlx.h"

int		main(int argc, char **argv)
{

	int		ret_code;
	t_data	*data;

	if ((ret_code = init(argc, argv, &data)) != OK)
		print_errors(ret_code, &data);
	free_data(&data);
	ft_printf("DONE\n");

	void	*mlx;
	void	*mlx_win;
	int		x;
	int		y;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 640, 480, "Hello world!");
	mlx_get_screen_size(mlx, &x, &y);
	ft_printf("%d %d\n", x, y);
	mlx_mouse_hide(mlx, mlx_win);
	mlx_loop(mlx);
	//(void) img;
	/*(void) mlx_win;
	if ((data_mlx.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data_mlx.mlx_win = mlx_new_window(data_mlx.mlx_ptr, 640, 480, "Hello world")) == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);*/
}

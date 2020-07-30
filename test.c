#include "srcs/cub3d.h"
#include "mlx.h"

int		main(int argc, char **argv)
{

	int		ret_code;
	t_data	*data;

	if ((ret_code = init(argc, argv, &data)) != OK)
		print_errors(ret_code, &data);

	data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, data->mlx.mlx_wid, data->mlx.mlx_hei,
		"Cub3d");
	mlx_mouse_hide(data->mlx.mlx, data->mlx.mlx_win);
	mlx_loop(data->mlx.mlx);
	/*(void) mlx_win;
	if ((data_mlx.mlx_ptr = mlx_init()) == NULL)
		return (EXIT_FAILURE);
	if ((data_mlx.mlx_win = mlx_new_window(data_mlx.mlx_ptr, 640, 480, "Hello world")) == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);*/
	free_data(&data);
	ft_printf("DONE\n");
}

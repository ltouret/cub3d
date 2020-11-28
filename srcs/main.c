/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:34:47 by ltouret           #+#    #+#             */
/*   Updated: 2020/11/28 18:24:22 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "bmp.h"

int		main(int argc, char **argv)
{
	int		ret_code;
	t_data	*data;

	if ((ret_code = init(argc, argv, &data)) != OK)
		print_errors(ret_code);
	if (argc == 3)
	{
		if ((ret_code = save_bmp(data)) != OK)
			print_errors(ret_code);
		exit_pro();
	}
	else
	{
		if (!(data->mlx.mlx_win = mlx_new_window(data->mlx.mlx,
			data->mlx.mlx_wid, data->mlx.mlx_hei, "Cub3d")))
			print_errors(ERR_MLX_INIT);
		mlx_mouse_hide(data->mlx.mlx, data->mlx.mlx_win);
		mlx_hook(data->mlx.mlx_win, 2, 1L << 0, keypress, data);
		mlx_hook(data->mlx.mlx_win, 3, 1L << 1, keyrelease, data);
		mlx_hook(data->mlx.mlx_win, 17, 1L << 17, exit_pro, data);
		create_image(data);
		mlx_loop_hook(data->mlx.mlx, player_movements, data);
		mlx_loop(data->mlx.mlx);
	}
}

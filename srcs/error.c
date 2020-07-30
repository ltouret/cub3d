/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 23:31:52 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/30 01:57:59 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_data(t_data **data)
{
	if (*data == NULL)
		return ;
	free((*data)->text_path.no_text);
	free((*data)->text_path.we_text);
	free((*data)->text_path.ea_text);
	free((*data)->text_path.so_text);
	free((*data)->text_path.s_text);
	//mlx_destroy_window((*data)->mlx.mlx, (*data)->mlx.mlx_win); // check if this is needed
	free_tab((*data)->map, 0);
	free(*data);
	*data = NULL;
}

static void	error_msgs2(char *err[100])
{
	err[30] = "Too few arguments provided";
	err[31] = "Too many arguments provided";
	err[32] = "Invalid argument provided";
	err[34] = "Invalid map file path";
	err[35] = "Invalid map file name";
	err[40] = "Missing map";
	err[41] = "Missing north texture";
	err[42] = "Missing south texture";
	err[43] = "Missing east texture";
	err[44] = "Missing west texture";
	err[45] = "Missing ceiling color";
	err[46] = "Missing floor color";
	err[47] = "Missing sprite texture";
	err[48] = "Missing resolution";
	err[49] = "Missing player in map";
	err[51] = "Error initializing mlx";
}

// TODO change err tab to real number cuz i created with one 100 error msgs
//		not the real number!
static void	error_msgs(int err_code, char *err[100])
{
	int		i;

	i = 0;
	while (i < 100)
		err[i++] = "Unknown error";
	if (err_code < 30)
	{
		err[2] = "Invalid resolution";
		err[3] = "Invalid texture path";
		err[4] = "Invalid color";
		err[5] = "Invalid color value";
		err[6] = "Map is not last";
		err[7] = "Duplicate map";
		err[8] = "Invalid map";
		err[11] = "Too many players";
		err[13] = "Duplicate key in map";
		err[14] = "Invalid key in map";
		err[21] = "Malloc error";
		err[28] = "Unknown error";
	}
	else
		error_msgs2(err);
	//err[] = "";
}

void		print_errors(int err_code, t_data **data)
{
	char	*err[100];

	if (err_code < 0 || err_code > 100)
		err_code = ERR_UK;
	error_msgs(err_code, err);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err[err_code], 2);
	ft_putstr_fd("\n", 2);
	free_data(data);
	exit(-1);
}

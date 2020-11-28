/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 23:31:52 by ltouret           #+#    #+#             */
/*   Updated: 2020/11/28 18:06:20 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	err[51] = "Initializing mlx";
	err[52] = "Error mlx";
	err[53] = "Cant write BMP";
}

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
}

void		print_errors(int err_code)
{
	char	*err[100];

	if (err_code < 0 || err_code > 100)
		err_code = ERR_UK;
	error_msgs(err_code, err);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err[err_code], 2);
	ft_putstr_fd("\n", 2);
	exit_pro();
}

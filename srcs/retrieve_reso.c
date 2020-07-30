/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_reso.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 18:09:33 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/30 02:04:27 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		num_len(int num)
{
	int		i;

	i = 0;
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

static int		max_reso(t_data *data)
{
	int		screen_x;
	int		screen_y;

	mlx_get_screen_size(data->mlx.mlx, &screen_x, &screen_y);
	ft_printf("%d %d\n", screen_x, screen_y);
	if (data->mlx.mlx_wid > screen_x || data->mlx.mlx_hei > screen_y)
		return (ERR_RES);
	return (OK);
}

int				get_reso(int *map_res, char *line, t_data *data)
{
	int		i;

	if (check_res(line) == ERR_RES)
		return (ERR_RES);
	i = 1;
	while (line[i] == ' ')
		i++;
	data->mlx.mlx_wid = ft_atoi(line + i);
	i += num_len(data->mlx.mlx_wid);
	while (line[i] == ' ')
		i++;
	data->mlx.mlx_hei = ft_atoi(line + i);
	if (max_reso(data) == ERR_RES)
		return (ERR_RES);
	i += num_len(data->mlx.mlx_hei);
	if (!(line[i] == '\0' && data->mlx.mlx_hei > 0 && data->mlx.mlx_wid > 0))
		return (ERR_RES);
	*map_res = 1;
	return (OK);
}

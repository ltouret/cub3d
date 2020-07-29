/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_reso.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 18:09:33 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/29 20:19:45 by ltouret          ###   ########.fr       */
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
	i += num_len(data->mlx.mlx_hei);
	if (!(line[i] == '\0' && data->mlx.mlx_hei > 0 && data->mlx.mlx_wid > 0))
		return (ERR_RES);
	*map_res = 1;
	return (OK);
}

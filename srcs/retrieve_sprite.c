/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 13:13:08 by ltouret           #+#    #+#             */
/*   Updated: 2020/10/27 23:41:00 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO create free func even if sprite_num == 0 needs to free sprite_ord && sprite_cords

int		init_sprite(t_data *data)
{
	int	i;

	if (!(data->mlx.sp_stc.z_buffer = malloc(sizeof(double) *
		data->mlx.mlx_wid)))
		return (ERR_MAL);
	if (!(data->mlx.sp_stc.sprite_ord = malloc(sizeof(int) *
		(data->mlx.sp_stc.sprite_num + 1))))
		return (ERR_MAL);
	if (!(data->mlx.sp_stc.sprite_cords = malloc(sizeof(double *) *
		(data->mlx.sp_stc.sprite_num + 1))))
		return (ERR_MAL);
	i = 0;
	while (i < data->mlx.sp_stc.sprite_num)
	{
		if (!(data->mlx.sp_stc.sprite_cords[i] = malloc(sizeof(double) * 3)))
			return (ERR_MAL);
		data->mlx.sp_stc.sprite_cords[i][0] = 0;
		data->mlx.sp_stc.sprite_cords[i][1] = 0;
		data->mlx.sp_stc.sprite_cords[i][2] = 0;
		i++;
	}
	data->mlx.sp_stc.sprite_cords[data->mlx.sp_stc.sprite_num] = NULL;
	return (OK);
}

void	retrieve_sprite(t_data *data, char *map_line)
{
	int	i;

	i = 0;
	while (map_line[i])
	{
		if (map_line[i] == '2')
		{
			data->mlx.sp_stc.sprite_cords[data->mlx.sp_stc.sprite_num][0] =
			i + 0.5;
			data->mlx.sp_stc.sprite_cords[data->mlx.sp_stc.sprite_num][1] =
			data->map_height + 0.5;
			data->mlx.sp_stc.sprite_ord[data->mlx.sp_stc.sprite_num] =
			data->mlx.sp_stc.sprite_num;
			data->mlx.sp_stc.sprite_num++;
		}
		i++;
	}
}
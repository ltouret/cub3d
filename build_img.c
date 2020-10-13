/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 19:57:10 by ltouret           #+#    #+#             */
/*   Updated: 2020/10/14 00:57:00 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/cub3d.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

void	draw_floor_ceil(t_data *data, t_img **img) // get his bs out of here
{
	int y;
	int x;

	y = 0;
	while (y < data->mlx.mlx_hei)
	{
		x = 0;
		while (x < data->mlx.mlx_wid)
		{
			(*img)->addr[y * data->mlx.mlx_wid + x] =
				data->color.f_color;
			(*img)->addr[(data->mlx.mlx_hei - y - 1) *
				data->mlx.mlx_wid + x] = data->color.c_color;
			x++;
		}
		y++;
	}
}

int		fill_image(t_data *data, t_img **img)
{
	if (!(*img = malloc(sizeof(t_img))))
		return (ERR_MAL);
	(*img)->img = mlx_new_image(data->mlx.mlx, data->mlx.mlx_wid, data->mlx.mlx_hei);
	(*img)->addr = (int *)mlx_get_data_addr((*img)->img, &(*img)->bpp,
	&(*img)->line_length, &(*img)->endian);
	draw_floor_ceil(data, img);
	ray(data, img);
	return (OK);
}

int		create_image(t_data *data)
{
	t_img	*img;
	int		ret_code;

	if ((ret_code = fill_image(data, &img) != OK))
		return (ret_code);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, img->img, 0, 0);
	mlx_destroy_image(data->mlx.mlx, img->img);
	free(img);
	return (OK);
}

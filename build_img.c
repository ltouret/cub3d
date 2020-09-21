/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 19:57:10 by ltouret           #+#    #+#             */
/*   Updated: 2020/09/21 20:20:34 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/cub3d.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

int		fill_image(t_data *data, t_img **img)
{
	if (!(*img = malloc(sizeof(t_img))))
		return (ERR_MAL);
	(*img)->img = mlx_new_image(data->mlx.mlx, data->mlx.mlx_wid, data->mlx.mlx_hei);
	(*img)->addr = mlx_get_data_addr((*img)->img, &(*img)->bits_per_pixel,
	&(*img)->line_length, &(*img)->endian);
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

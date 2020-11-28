/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 19:57:10 by ltouret           #+#    #+#             */
/*   Updated: 2020/11/28 17:33:47 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/cub3d.h"
#include "mlx.h"

static void	draw_floor_ceil(t_data *data, t_img **img)
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

static void	draw_wall(t_data *data, t_img **img)
{
	int		x;
	int		side;

	x = 0;
	while (x < data->mlx.mlx_wid)
	{
		data->mlx.ray_dirs[0] = data->player.dir_x + data->player.plane_x *
			(2 * x / (double)data->mlx.mlx_wid - 1);
		data->mlx.ray_dirs[1] = data->player.dir_y + data->player.plane_y *
			(2 * x / (double)data->mlx.mlx_wid - 1);
		data->mlx.map_cords[0] = (int)data->player.x;
		data->mlx.map_cords[1] = (int)data->player.y;
		wall_casting(data);
		wall_casting2(data, &side);
		wall_casting3(data, side);
		wall_casting4(data, side, x, img);
		data->mlx.sp_stc.z_buffer[x] = data->mlx.wall_dist;
		x++;
	}
}

static void	draw_sprite(t_data *data, t_img **img)
{
	int		i;
	double	sprite_cam[2];
	double	trans_cords[2];

	i = 0;
	sprite_casting(data);
	while (i < data->mlx.sp_stc.sprite_num)
	{
		sprite_casting1(data, i, sprite_cam, trans_cords);
		sprite_casting2(data, trans_cords);
		sprite_casting3(data, trans_cords, img);
		i++;
	}
}

int			fill_image(t_data *data, t_img **img)
{
	if (!(*img = malloc(sizeof(t_img))))
		return (ERR_MAL);
	(*img)->img = mlx_new_image(data->mlx.mlx, data->mlx.mlx_wid,
		data->mlx.mlx_hei);
	(*img)->addr = (int *)mlx_get_data_addr((*img)->img, &(*img)->bpp,
		&(*img)->line_length, &(*img)->endian);
	draw_floor_ceil(data, img);
	draw_wall(data, img);
	draw_sprite(data, img);
	return (OK);
}

int			create_image(t_data *data)
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

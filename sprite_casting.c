/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 00:18:39 by ltouret           #+#    #+#             */
/*   Updated: 2020/11/26 00:18:42 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/cub3d.h"

void	sprite_casting(t_data *data)
{
	int i;

	i = 0;
	while (i < data->mlx.sp_stc.sprite_num)
	{
		data->mlx.sp_stc.sprite_ord[i] = i;
		data->mlx.sp_stc.sprite_cords[i][2] = ((data->player.x -
			data->mlx.sp_stc.sprite_cords[i][0])
			* (data->player.x - data->mlx.sp_stc.sprite_cords[i][0])
			+ (data->player.y - data->mlx.sp_stc.sprite_cords[i][1])
			* (data->player.y - data->mlx.sp_stc.sprite_cords[i][1]));
		i++;
	}
	sort_sprites(data);
}

void	sprite_casting1(t_data *data, int i, double *sprite_cam,
	double *trans_cords)
{
	sprite_cam[0] = data->mlx.sp_stc.sprite_cords
		[data->mlx.sp_stc.sprite_ord[i]][0] - data->player.x;
	sprite_cam[1] = data->mlx.sp_stc.sprite_cords
		[data->mlx.sp_stc.sprite_ord[i]][1] - data->player.y;
	trans_cords[0] = 1.0 / (data->player.plane_x * data->player.dir_y -
	data->player.dir_x * data->player.plane_y) * (data->player.dir_y *
	sprite_cam[0] - data->player.dir_x * sprite_cam[1]);
	trans_cords[1] = 1.0 / (data->player.plane_x * data->player.dir_y -
	data->player.dir_x * data->player.plane_y) * (-data->player.plane_y *
	sprite_cam[0] + data->player.plane_x * sprite_cam[1]);
}

void	sprite_casting2(t_data *data, double *trans_cords)
{
	data->mlx.sp_stc.sprite_screen = (int)((data->mlx.mlx_wid / 2) *
		(1 + trans_cords[0] / trans_cords[1]));
	data->mlx.sp_stc.sprite_hei = abs((int)(data->mlx.mlx_hei /
		(trans_cords[1]))) / 1;
	data->mlx.sp_stc.draw_y[0] = -data->mlx.sp_stc.sprite_hei /
		2 + data->mlx.mlx_hei / 2 + ((int)(0 / trans_cords[1]));
	if (data->mlx.sp_stc.draw_y[0] < 0)
		data->mlx.sp_stc.draw_y[0] = 0;
	data->mlx.sp_stc.draw_y[1] = data->mlx.sp_stc.sprite_hei /
		2 + data->mlx.mlx_hei / 2 + ((int)(0 / trans_cords[1]));
	if (data->mlx.sp_stc.draw_y[1] >= data->mlx.mlx_hei)
		data->mlx.sp_stc.draw_y[1] = data->mlx.mlx_hei - 1;
	data->mlx.sp_stc.sprite_wid = abs((int)(data->mlx.mlx_hei /
		(trans_cords[1]))) / 1;
	data->mlx.sp_stc.draw_x[0] = -data->mlx.sp_stc.sprite_hei / 2 +
		data->mlx.sp_stc.sprite_screen;
	if (data->mlx.sp_stc.draw_x[0] < 0)
		data->mlx.sp_stc.draw_x[0] = 0;
	data->mlx.sp_stc.draw_x[1] = data->mlx.sp_stc.sprite_wid / 2 +
		data->mlx.sp_stc.sprite_screen;
	if (data->mlx.sp_stc.draw_x[1] >= data->mlx.mlx_wid)
		data->mlx.sp_stc.draw_x[1] = data->mlx.mlx_wid - 1;
}

void	sprite_casting3(t_data *data, double *trans_cords, t_img **img)
{
	int	tex_x;

	while (data->mlx.sp_stc.draw_x[0] < data->mlx.sp_stc.draw_x[1])
	{
		tex_x = (int)(256 * (data->mlx.sp_stc.draw_x[0] -
		(-data->mlx.sp_stc.sprite_wid / 2 + data->mlx.sp_stc.sprite_screen))
		* data->mlx.sp_stc.sp_text.wid / data->mlx.sp_stc.sprite_wid) / 256;
		if (trans_cords[1] > 0 && data->mlx.sp_stc.draw_x[0] > 0 &&
			data->mlx.sp_stc.draw_x[0] < data->mlx.mlx_wid && trans_cords[1] <
			data->mlx.sp_stc.z_buffer[data->mlx.sp_stc.draw_x[0]])
		{
			sprite_casting4(data, tex_x, img);
		}
		data->mlx.sp_stc.draw_x[0]++;
	}
}

void	sprite_casting4(t_data *data, int tex_x, t_img **img)
{
	int	y;
	int	d;
	int	tex_y;
	int	color;

	y = data->mlx.sp_stc.draw_y[0];
	while (y < data->mlx.sp_stc.draw_y[1])
	{
		d = (y) * 256 - data->mlx.mlx_hei * 128 +
		data->mlx.sp_stc.sprite_hei * 128;
		tex_y = ((d * data->mlx.sp_stc.sp_text.hei) /
		data->mlx.sp_stc.sprite_hei) / 256;
		color = data->mlx.sp_stc.sp_text.addr
		[data->mlx.sp_stc.sp_text.wid * tex_y + tex_x];
		if ((color & 0x00FFFFFF) != 0)
			(*img)->addr[y * data->mlx.mlx_wid +
				data->mlx.sp_stc.draw_x[0]] = color;
		y++;
	}
}

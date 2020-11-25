/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_casting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 21:09:19 by ltouret           #+#    #+#             */
/*   Updated: 2020/11/25 22:11:25 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/cub3d.h"
#include <math.h>

void	wall_casting(t_data *data)
{
	if (data->mlx.ray_dirs[0] < 0)
	{
		data->mlx.steps[0] = -1;
		data->mlx.side_dists[0] = (data->player.x - (int)data->player.x) *
			(fabs(1 / data->mlx.ray_dirs[0]));
	}
	else
	{
		data->mlx.steps[0] = 1;
		data->mlx.side_dists[0] = ((int)data->player.x + 1.0 - data->player.x) *
			(fabs(1 / data->mlx.ray_dirs[0]));
	}
	if (data->mlx.ray_dirs[1] < 0)
	{
		data->mlx.steps[1] = -1;
		data->mlx.side_dists[1] = (data->player.y - (int)data->player.y) *
			(fabs(1 / data->mlx.ray_dirs[1]));
	}
	else
	{
		data->mlx.steps[1] = 1;
		data->mlx.side_dists[1] = ((int)data->player.y + 1.0 - data->player.y) *
			(fabs(1 / data->mlx.ray_dirs[1]));
	}
}

void	wall_casting2(t_data *data, int *side)
{
	while (1)
	{
		if (data->mlx.side_dists[0] < data->mlx.side_dists[1])
		{
			data->mlx.side_dists[0] += fabs(1 / data->mlx.ray_dirs[0]);
			data->mlx.map_cords[0] += data->mlx.steps[0];
			*side = 0;
		}
		else
		{
			data->mlx.side_dists[1] += fabs(1 / data->mlx.ray_dirs[1]);
			data->mlx.map_cords[1] += data->mlx.steps[1];
			*side = 1;
		}
		if (data->map[data->mlx.map_cords[1]][data->mlx.map_cords[0]] == '1')
			break ;
	}
}

void	wall_casting3(t_data *data, int side)
{
	if (side == 0)
		data->mlx.wall_dist = (data->mlx.map_cords[0] - data->player.x +
			(1 - data->mlx.steps[0]) / 2) / data->mlx.ray_dirs[0];
	else
		data->mlx.wall_dist = (data->mlx.map_cords[1] - data->player.y +
			(1 - data->mlx.steps[1]) / 2) / data->mlx.ray_dirs[1];
	data->mlx.draw_wall[0] = -(int)(data->mlx.mlx_hei / data->mlx.wall_dist) /
		2 + data->mlx.mlx_hei / 2;
	if (data->mlx.draw_wall[0] < 0)
		data->mlx.draw_wall[0] = 0;
	data->mlx.draw_wall[1] = (int)(data->mlx.mlx_hei / data->mlx.wall_dist) /
		2 + data->mlx.mlx_hei / 2;
	if (data->mlx.draw_wall[1] >= data->mlx.mlx_hei)
		data->mlx.draw_wall[1] = data->mlx.mlx_hei - 1;
	if (side == 0 && data->mlx.ray_dirs[0] > 0)
		data->mlx.chosen_text = &data->mlx.ea_text;
	else if (side == 0 && data->mlx.ray_dirs[0] < 0)
		data->mlx.chosen_text = &data->mlx.we_text;
	else if (side == 1 && data->mlx.ray_dirs[1] > 0)
		data->mlx.chosen_text = &data->mlx.so_text;
	else
		data->mlx.chosen_text = &data->mlx.no_text;
}

void	wall_casting4(t_data *data, int side, int x, t_img **img)
{
	double	tex_pos;
	int		tex_cords[2];
	int		color;

	tex_pos = wall_casting5(data, side, tex_cords);
	while (data->mlx.draw_wall[0] < data->mlx.draw_wall[1])
	{
		tex_cords[1] = (int)tex_pos & (data->mlx.chosen_text->hei - 1);
		tex_pos += 1.0 * data->mlx.chosen_text->wid /
			(int)(data->mlx.mlx_hei / data->mlx.wall_dist);
		color = data->mlx.chosen_text->addr[data->mlx.chosen_text->wid *
			tex_cords[1] + tex_cords[0]];
		(*img)->addr[data->mlx.draw_wall[0] * data->mlx.mlx_wid + x] = color;
		data->mlx.draw_wall[0]++;
	}
}

double	wall_casting5(t_data *data, int side, int *tex_cords)
{
	double	wall_x;
	double	tex_pos;

	wall_x = (side == 0) ? data->player.y + data->mlx.wall_dist *
		data->mlx.ray_dirs[1]
		: data->player.x + data->mlx.wall_dist * data->mlx.ray_dirs[0];
	wall_x -= floor((wall_x));
	tex_cords[0] = (int)(wall_x * (double)(data->mlx.chosen_text->wid));
	if (side == 0 && data->mlx.ray_dirs[0] > 0)
		tex_cords[0] = data->mlx.chosen_text->wid - tex_cords[0] - 1;
	if (side == 1 && data->mlx.ray_dirs[1] < 0)
		tex_cords[0] = data->mlx.chosen_text->wid - tex_cords[0] - 1;
	tex_pos = (data->mlx.draw_wall[0] - data->mlx.mlx_hei
			/ 2 + (int)(data->mlx.mlx_hei / data->mlx.wall_dist) / 2) *
			1.0 * data->mlx.chosen_text->wid /
			(int)(data->mlx.mlx_hei / data->mlx.wall_dist);
	return (tex_pos);
}

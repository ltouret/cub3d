/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 16:50:54 by ltouret           #+#    #+#             */
/*   Updated: 2020/11/28 18:22:41 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "player_mov.h"
#include <math.h>

void	rotate_player(t_data *data, int flag)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = data->player.rot_speed;
	rot_speed *= (ft_find("NE", data->player.ori) != -1 ? -1 : 1) * flag;
	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(rot_speed) -
	data->player.dir_y * sin(rot_speed);
	data->player.dir_y = old_dir_x * sin(rot_speed) + data->player.dir_y *
	cos(rot_speed);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(rot_speed) -
	data->player.plane_y * sin(rot_speed);
	data->player.plane_y = old_plane_x * sin(rot_speed) +
	data->player.plane_y * cos(rot_speed);
}

void	move_player_ns(t_data *data, int flag)
{
	double	mov_speed;

	mov_speed = data->player.mov_speed * flag;
	if (data->map[(int)(data->player.y + data->player.dir_y * mov_speed *
		data->player.radius)][(int)(data->player.x)] == '0')
		data->player.y += data->player.dir_y * mov_speed;
	if (data->map[(int)(data->player.y)][(int)(data->player.x +
		data->player.dir_x * mov_speed * data->player.radius)] == '0')
		data->player.x += data->player.dir_x * mov_speed;
}

void	move_player_we(t_data *data, int flag)
{
	double	mov_speed;

	mov_speed = data->player.mov_speed * flag;
	if (data->map[(int)(data->player.y + data->player.plane_y * mov_speed *
		data->player.radius)][(int)(data->player.x)] == '0')
		data->player.y += data->player.plane_y * mov_speed;
	if (data->map[(int)(data->player.y)][(int)(data->player.x +
		data->player.plane_x * mov_speed * data->player.radius)] == '0')
		data->player.x += data->player.plane_x * mov_speed;
}

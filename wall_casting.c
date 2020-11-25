#include "srcs/cub3d.h"
#include "mlx.h"
#include "bmp.h"
#include "player_mov.h"
#include <stdio.h>
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

//change perpWallDist to unicase
void	wall_casting3(t_data *data, int side, double *perpWallDist)
{
	if (side == 0)
		*perpWallDist = (data->mlx.map_cords[0] - data->player.x +
			(1 - data->mlx.steps[0]) / 2) / data->mlx.ray_dirs[0];
	else
		*perpWallDist = (data->mlx.map_cords[1] - data->player.y +
			(1 - data->mlx.steps[1]) / 2) / data->mlx.ray_dirs[1];
	data->mlx.draw[0] = -(int)(data->mlx.mlx_hei / *perpWallDist) /
		2 + data->mlx.mlx_hei / 2;
	if (data->mlx.draw[0] < 0)
		data->mlx.draw[0] = 0;
	data->mlx.draw[1] = (int)(data->mlx.mlx_hei / *perpWallDist) /
		2 + data->mlx.mlx_hei / 2;
	if (data->mlx.draw[1] >= data->mlx.mlx_hei)
		data->mlx.draw[1] = data->mlx.mlx_hei - 1;
	if (side == 0 && data->mlx.ray_dirs[0] > 0)
		data->mlx.chosen_text = &data->mlx.ea_text;
	else if (side == 0 && data->mlx.ray_dirs[0] < 0)
		data->mlx.chosen_text = &data->mlx.we_text;
	else if (side == 1 && data->mlx.ray_dirs[1] > 0)
		data->mlx.chosen_text = &data->mlx.so_text;
	else
		data->mlx.chosen_text = &data->mlx.no_text;
}

//void	wall_casting4(t_data *data, int side, double perpWallDist, int x, t_img **img)

void	wall_casting4(t_data *data, int side, double perpWallDist, int x, t_img **img)
{
	double	wallX;
	double	tex_pos;
	int		tex_cords[2];
	int		color;

	wallX = (side == 0) ? data->player.y + perpWallDist *
		data->mlx.ray_dirs[1]
		: data->player.x + perpWallDist * data->mlx.ray_dirs[0];
	wallX -= floor((wallX));
	tex_cords[0] = (int)(wallX * (double)(data->mlx.chosen_text->wid));
	if (side == 0 && data->mlx.ray_dirs[0] > 0)
		tex_cords[0] = data->mlx.chosen_text->wid - tex_cords[0] - 1;
	if (side == 1 && data->mlx.ray_dirs[1] < 0)
		tex_cords[0] = data->mlx.chosen_text->wid - tex_cords[0] - 1;
	tex_pos = (data->mlx.draw[0]- data->mlx.mlx_hei
			/ 2 + (int)(data->mlx.mlx_hei / perpWallDist) / 2) *
			1.0 * data->mlx.chosen_text->wid /
			(int)(data->mlx.mlx_hei / perpWallDist);
	while (data->mlx.draw[0] < data->mlx.draw[1])
	{
		tex_cords[1] = (int)tex_pos & (data->mlx.chosen_text->hei - 1);
		tex_pos += 1.0 * data->mlx.chosen_text->wid /
			(int)(data->mlx.mlx_hei / perpWallDist);
		color = data->mlx.chosen_text->addr[data->mlx.chosen_text->wid *
			tex_cords[1] + tex_cords[0]];
		(*img)->addr[data->mlx.draw[0] * data->mlx.mlx_wid + x] = color;
		data->mlx.draw[0]++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 16:08:52 by ltouret           #+#    #+#             */
/*   Updated: 2020/09/18 15:21:43 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/cub3d.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

double	degreeToRadians(double degree)
{
	return (degree * M_PI / 180.0);
}

void            my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	ray(t_data *data, t_img *img)
{
	int		screen_half_x = data->mlx.mlx_wid / 2;
	int		screen_half_y = data->mlx.mlx_hei / 2;
	int		render_delay = 30;
	double	player_angle = data->player.ori;
	double	fov = 60.0;
	double	half_fov = fov / 2;
	double	rayc_incr_angle = fov / data->mlx.mlx_wid;
	double	rayc_pre = 10000;

	//ft_printf("%d %d\n", screen_half_x, screen_half_y);

	// actual raycasting
	double	ray_angle = player_angle - half_fov;
	int ray_count = 0;
	while (ray_count < data->mlx.mlx_wid)
	{
		double mapX = data->player.x; 
		double mapY = data->player.y; 

		double rayCos = cos(degreeToRadians(ray_angle)) / rayc_pre;
		double raySin = sin(degreeToRadians(ray_angle)) / rayc_pre;

		int wall = 0;
		while (wall != '1')
		{
			mapX += rayCos;
			mapY += raySin;
			wall = data->map[(int)floor(mapY)][(int)floor(mapX)];
			//if (wall == '1')
			//	ft_printf("%d %d %c\n",(int) mapX,(int) mapY, wall);
		}
		double distance = sqrt(pow(data->player.x - mapX, 2) + pow(data->player.y - mapY, 2));
		distance *= cos(degreeToRadians(ray_angle - player_angle)); 
		//distance = (distance < 1) ? 1 : distance;

		int wallhei = (int)(screen_half_y / (distance));
		printf("x = %d dist %f wallhei: %d play %f %f\n", ray_count, distance, wallhei, data->player.x, data->player.y);
		//printf("x = %d cei %d, wall %d %d, floor %d\n", ray_count, screen_half_y - wallhei, screen_half_y - wallhei, screen_half_y + wallhei, screen_half_y + wallhei);

		int drawStart = 0;
		int drawEnd = screen_half_y - wallhei;
		//printf("%d %d %d\n", wallhei, drawStart, drawEnd);
		//TODO check print pixels, algunos pixeles se estan llenando de ceiling y walls or walls y floor! 
		draw_vert(img, ray_count, drawStart, drawEnd, data, 0x00FFFF);
		draw_vert(img, ray_count, screen_half_y - wallhei, screen_half_y + wallhei, data, 0x00FF0000);
		draw_vert(img, ray_count, screen_half_y + wallhei, data->mlx.mlx_hei, data, 0x0000AA00);
		ray_angle += rayc_incr_angle;
		ray_count++;
	}
}

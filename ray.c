/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 16:08:52 by ltouret           #+#    #+#             */
/*   Updated: 2020/10/17 12:19:15 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srcs/cub3d.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

/*double	degreeToRadians(double degree)
{
	return (degree * M_PI / 180.0);
}

void            my_mlx_pixel_put(t_img **img, int x, int y, int color)
{
    char    *dst;

    dst = (*img)->addr + (y * (*img)->line_length + x * ((*img)->bpp / 8));
    *(unsigned int*)dst = color;
}

void	ray(t_data *data, t_img **img)
{
	int		screen_half_x = data->mlx.mlx_wid / 2;
	int		screen_half_y = data->mlx.mlx_hei / 2;
	double	fov = 60.0;
	double	half_fov = fov / 2;
	double	rayc_incr_angle = fov / data->mlx.mlx_wid;
	double	rayc_pre = 1000;

	//ft_printf("%d %d\n", screen_half_x, screen_half_y);

	// actual raycasting
	double	ray_angle = data->player.ori- half_fov;
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
			wall = data->map[(int)mapY][(int)mapX];
			//if (wall == '1')
			//	ft_printf("%d %d %c\n",(int) mapX,(int) mapY, wall);
		}
		//printf("ray_ang %d ray_c %d X %f Y %f\n", 90 - (int)ray_angle % 90, ray_count, mapX, mapY);
		if (1)
		{
			double Ay;
			double Ax;
			double Ya;
			double Xa;
			if (data->player.ori > 180)
			{
				Ay = ((int)(data->player.y / 1)) * 1 - 1;
				Ya = -1;
			}
			else
			{
				Ay = ((int)(data->player.y / 1)) * 1 + 1;
				Ya = 1;
			}
			Ax = (int)(data->player.x + ((data->player.y - Ay) / ? :tan(degreeToRadians(abs(360 - ray_angle)))));
			//printf("x %d int %c\n", ray_count, data->map[(int)Ay][(int)Ax]);
			Xa = 1 / tan(degreeToRadians(ray_angle));
			printf("x %d alpha %f ori %f Ay %f Ax %f Xa %f\n", ray_count, ray_angle, data->player.ori, Ay, Ax, Xa);
		}
		double distance = sqrt(pow(data->player.x - mapX, 2) + pow(data->player.y - mapY, 2));
		distance *= cos(degreeToRadians(ray_angle - data->player.ori)); 
		//distance = (distance < 1) ? 1 : distance;

		int wallhei = (int)(screen_half_y / (distance));
		//printf("x = %d dist %f wallhei: %d play %f %f\n", ray_count, distance, wallhei, data->player.x, data->player.y);
		//printf("x = %d cei %d, wall %d %d, floor %d\n", ray_count, screen_half_y - wallhei, screen_half_y - wallhei, screen_half_y + wallhei, screen_half_y + wallhei);

		int drawStart = 0;
		int drawEnd = screen_half_y - wallhei;
		//printf("%d %d %d\n", wallhei, drawStart, drawEnd);
		//TODO check print pixels, algunos pixeles se estan llenando de ceiling y walls or walls y floor! 
		//draw_vert(img, ray_count, drawStart, drawEnd, data, 0x00FFFF);
		draw_vert(img, ray_count, screen_half_y - wallhei, screen_half_y + wallhei, data, 0x00FF0000);
		//draw_vert(img, ray_count, screen_half_y + wallhei, data->mlx.mlx_hei, data, 0x0000AA00);
		ray_angle += rayc_incr_angle;
		ray_count++;
	}
}*/

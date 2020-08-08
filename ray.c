/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 16:08:52 by ltouret           #+#    #+#             */
/*   Updated: 2020/08/08 18:00:37 by ltouret          ###   ########.fr       */
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
	return (degree * M_PI / 180);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
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
	double	fov = 60;
	double	half_fov = fov / 2;
	double	player_angle = 90;
	double	rayc_incr_angle = fov / data->mlx.mlx_wid;
	double	rayc_pre = 64;

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
		//printf("dist %f\n", distance);

		int wallhei = (int)floor(screen_half_y / distance);
		printf("cei %d, wall %d %d, floor %d\n", 0, screen_half_y - wallhei, screen_half_y + wallhei, 480);

		int drawStart = 0;
		int drawEnd = screen_half_y - wallhei;
		//TODO cehck why its broken with pixel print! maybe out of the lista? acuerdate q estas entrando a 0 hasta 480 puede que no halla indice 0 o 480?
		//draw_vert(img, ray_count, drawStart, drawEnd, data, 0x00FF0000);
		ray_angle += rayc_incr_angle;
		ray_count++;
	}
}

#include "srcs/cub3d.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

#define mapWidth 24
#define mapHeight 24

/*int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};*/

void	print_map(char **map)
{
	int		i;

	i = 0;
	ft_printf("Parsed map is:\n");
	while (map[i])
		ft_printf("%s\n", map[i++]);
}

void	ray(t_data *data)
{
	char **worldMap = data->map;
	double posX = data->player.x, posY = data->player.y;  //x and y start position
	//ft_printf("%d %d",(int) posY, (int)posX);
	//double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	int x;
	int h;
	int w;

	x = 0;
	h = data->mlx.mlx_hei;
	w = data->mlx.mlx_wid;
	while (x < w)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//ft_printf("%d\n", x);

		int mapX = (int)posX;
		int mapY = (int)posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (rayDirX < 0)
		{
		  stepX = -1;
		  sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
		  stepX = 1;
		  sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
		  stepY = -1;
		  sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
		  stepY = 1;
		  sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
		  //jump to next map square, OR in x-direction, OR in y-direction
		  if (sideDistX < sideDistY)
		  {
		    sideDistX += deltaDistX;
		    mapX += stepX;
		    side = 0;
		  }
		  else
		  {
		    sideDistY += deltaDistY;
		    mapY += stepY;
		    side = 1;
		  }
		  ft_printf("this is x %d : %d %d and %d %d and %c\n", x,(int) sideDistY, (int) sideDistY, mapX, mapY, worldMap[mapY][mapX]);
		  //Check if ray has hit a wall
		   if (worldMap[mapY][mapX] == '1') hit = 1;
		} 
		if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
      else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h)drawEnd = h - 1;
		// TODO add color stuff here!
	/* color;
      switch(worldMap[mapX][mapY])
      {
        case 1:  color = RGB_Red;  break; //red
        case 2:  color = RGB_Green;  break; //green
        case 3:  color = RGB_Blue;   break; //blue
        case 4:  color = RGB_White;  break; //white
        default: color = RGB_Yellow; break; //yellow
      }

      //give x and y sides different brightness
      if (side == 1) {color = color / 2;}
*/
      //draw the pixels of the stripe as a vertical line
     // verLine(x, drawStart, drawEnd, color);
		x++;
	}
}

typedef struct  ss_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}				ts_data;

void            my_mlx_pixel_put(ts_data *ddata, int x, int y, int color)
{
    char    *dst;

    dst = ddata->addr + (y * ddata->line_length + x * (ddata->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		main(int argc, char **argv)
{

	int		ret_code;
	t_data	*data;
	ts_data img;

	if ((ret_code = init(argc, argv, &data)) != OK)
		print_errors(ret_code, &data);
	//ft_printf("%d %d\n", (int)data->player.x, (int)data->player.y);
	//ray(data);
	//print_map(data->map);
	if (!(data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, data->mlx.mlx_wid,
		data->mlx.mlx_hei, "Cub3d")))
		print_errors(ERR_MLX_INIT, &data);
	mlx_mouse_hide(data->mlx.mlx, data->mlx.mlx_win);
	img.img = mlx_new_image(data->mlx.mlx, data->mlx.mlx_wid, data->mlx.mlx_hei);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
	int y;
	int x;
	img.addr[3] = 97;
	char *dst;
	dst = img.addr + 0 + 4 * 520 * 188;
	*(unsigned int *)dst =  0x00FF0000;
	dst = img.addr + 0 + 4 * 520 * 292;
	*(unsigned int *)dst =  0x00FF0000;
	img.addr[0 + 4 * 520 * 292 + 1] = 255;
	x = 0;
	while (x < 540)
	{
		y = 0;
		while (y < 400)
		{
			//my_mlx_pixel_put(&img, 5, 50, 0x00FF0000);
			//my_mlx_pixel_put(&img, 0, 0, 0x00FFFFFF);
			y++;
		}
		x++;
	}
	int w = -1;
	while (++w < 11)
	{
		printf("%d %d %s\n", img.addr[w], w, w % 3 != 0 ? "" : "alpha vla" );
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.mlx_win, img.img, 0, 0);
	mlx_loop(data->mlx.mlx);
	free_data(&data);
	ft_printf("DONE\n");
}

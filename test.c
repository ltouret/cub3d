#include "srcs/cub3d.h"
#include "mlx.h"
#include "player_mov.h"
#include <stdio.h>
#include <math.h>

#define mapWidth 24
#define mapHeight 24

//this has to be in the Makefile
#define LINUX 1

// keys.h
#define LIN_KEY_W 119
#define LIN_KEY_A 97
#define LIN_KEY_S 115
#define LIN_KEY_D 100
#define LIN_KEY_UP 65362
#define LIN_KEY_LEFT 65361
#define LIN_KEY_DOWN 65364
#define LIN_KEY_RIGHT 65363
#define LIN_KEY_ESC 65307 // maybe not needed esc

#define MAC_KEY_W 13
#define MAC_KEY_A 0
#define MAC_KEY_S 1
#define MAC_KEY_D 2
#define MAC_KEY_UP 126
#define MAC_KEY_LEFT 123
#define MAC_KEY_DOWN 125
#define MAC_KEY_RIGHT 124
#define MAC_KEY_ESC 53 // maybe not needed esc

void			draw_pixel(t_img **img, int x, int y, t_data *data, int color)
{
	char *dst;

    dst = (*img)->addr + (y * (*img)->line_length + x * ((*img)->bpp / 8));
	*(unsigned int *)dst =  color;
}

void			draw_vert(t_img **img, int x, int y1, int y2, t_data *data, int color)
{
	int i;

	i = y1 - 1;
	/*if (i > data->mlx.mlx_hei)
		i = data->mlx.mlx_hei;
	if (y2 < 0)
		y2 = 0;
	if (i < 0)
		i = 0; 
	if (y2 > data->mlx.mlx_hei)
		y2 = data->mlx.mlx_hei;*/
	//printf("x %d y1 %d y2 %d\n", x, i, y2);
	while (++i <= y2)
	{
		//printf("im %d\n", i);
		draw_pixel(img, x, i, data, color);
	}
}

void	print_map(char **map)
{
	int		i;

	i = 0;
	ft_printf("Parsed map is:\n");
	while (map[i])
		ft_printf("%s\n", map[i++]);
}

void	ray(t_data *data, t_img **img)
{
	char **worldMap = data->map;
	double posX = data->player.x, posY = data->player.y;  //x and y start position
	//ft_printf("%d %d",(int) posY, (int)posX);
	//double posX = 22, posY = 12;  //x and y start position
	//double dirX = 0, dirY = 1; //initial direction vector
	//double planeX = 0.66, planeY = 0; //the 2d raycaster version of camera plane

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
		double rayDirX = data->player.dir_x + data->player.plane_x * cameraX;
		double rayDirY = data->player.dir_y + data->player.plane_y * cameraX;
		//ft_printf("%d\n", x);

		int mapX = (int)posX;
		int mapY = (int)posY;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
		//double deltaDistX = fabs(1 / rayDirX);
		//double deltaDistY = fabs(1 / rayDirY); 
		//printf("x is : %d ray: %f %f, delta %f %f\n",x, rayDirX, rayDirY, deltaDistX, deltaDistY);
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
		  //printf("this is x %d dist: %f %f and %d %d and %c side : %d\n", x, sideDistY, sideDistX, mapX, mapY, worldMap[mapY][mapX], side);
		  //Check if ray has hit a wall
		   if (data->map[mapY][mapX] == '1') hit = 1;
		} 
		//printf("x %d side %d\n", x, side);
		if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
      else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if (drawEnd >= h)drawEnd = h - 1;
		//printf("x :%d --> %d %d\n", x , drawStart, drawEnd);
		//int color;
		int no_color = 0x00FF0000;
		int so_color = 0x0000FF00;
		int ea_color = 0x000000FF;
		int we_color = 0x00FFFF66;
		// TODO add color stuff here!
	 /*color;
      switch(worldMap[mapX][mapY])
      {
        case 1:  color = RGB_Red;  break; //red
        case 2:  color = RGB_Green;  break; //green
        case 3:  color = RGB_Blue;   break; //blue
        case 4:  color = RGB_White;  break; //white
        default: color = RGB_Yellow; break; //yellow
      }*/

      //give x and y sides different brightness
      //if (side == 0 && 0.66 >= data->player.plane_x && data->player.plane_x >= -0.66 && data->player.plane_y >= 0) // y is true 
      if (side == 0 && 1 >= rayDirY && rayDirY >= -1 &&
		  1.2 >= rayDirX && rayDirX >= 0.657938)// && data->player.plane_y >= 0) // y is true 
		draw_vert(img, x, drawStart, drawEnd, data, no_color);
      //else if (side == 0 && 0.66 >= data->player.plane_x && data->player.plane_x >= -0.66 && data->player.plane_y <= 0)
	//	draw_vert(img, x, drawStart, drawEnd, data, we_color);
	else // y is false
		draw_vert(img, x, drawStart, drawEnd, data, ea_color);
		printf("x %d pX %f pY %f\n", x, rayDirX, rayDirY);

      //draw the pixels of the stripe as a vertical line
     // verLine(x, drawStart, drawEnd, color);
		x++;
	}
}

int		active_key(t_data *data)
{
	if (data->keys[MAC_KEY_W] || data->keys[MAC_KEY_A] || data->keys[MAC_KEY_D]
		|| data->keys[MAC_KEY_S] || data->keys[MAC_KEY_UP] ||
		data->keys[MAC_KEY_DOWN] || data->keys[MAC_KEY_LEFT] ||
		data->keys[MAC_KEY_RIGHT] || data->keys[MAC_KEY_ESC])
		return (OK);
	return (ERR);
}

int		player_movements(t_data *data)
{
	if (active_key(data))
	{
		if (data->keys[MAC_KEY_LEFT])
			rotate_player(data, ROT_LEFT);
		if (data->keys[MAC_KEY_RIGHT])
			rotate_player(data, ROT_RIGHT);
		if (data->keys[MAC_KEY_UP] || data->keys[MAC_KEY_W])
			move_player_ns(data, MOV_W);
		if (data->keys[MAC_KEY_DOWN] || data->keys[MAC_KEY_S])
			move_player_ns(data, MOV_S);
		if (data->keys[MAC_KEY_D])
			move_player_we(data, MOV_D);
		if (data->keys[MAC_KEY_A])
			move_player_we(data, MOV_A);
		create_image(data);
		//printf("pX %f pY %f\n", data->player.dir_x, data->player.dir_y);
	}
	return (OK);
}

int		linux_mac_keycode(int *keycode)
{
	if (*keycode == LIN_KEY_W)
		*keycode = MAC_KEY_W;
	else if (*keycode == LIN_KEY_A)
		*keycode = MAC_KEY_A;
	else if (*keycode == LIN_KEY_S)
		*keycode = MAC_KEY_S;
	else if (*keycode == LIN_KEY_D)
		*keycode = MAC_KEY_D;
	else if (*keycode == LIN_KEY_UP)
		*keycode = MAC_KEY_UP;
	else if (*keycode == LIN_KEY_DOWN)
		*keycode = MAC_KEY_DOWN;
	else if (*keycode == LIN_KEY_LEFT)
		*keycode = MAC_KEY_LEFT;
	else if (*keycode == LIN_KEY_RIGHT)
		*keycode = MAC_KEY_RIGHT;
	return (OK);
}

void	show_key(t_data *data)
{
	int i = -1;
	while (++i < 280)
	{
		ft_printf("i %d act_key %d\n", i, data->keys[i]);
	}
}

int		keypress(int keycode, t_data *data)
{
	//if (keycode == 65307); // exit program
	//ft_printf("pressed ");
	//ft_printf("LIN key is: %d\n", keycode);
	if (LINUX)
		linux_mac_keycode(&keycode);
	if (keycode < 280)
		data->keys[keycode] = 1;
	//show_key(data);
	//ft_printf("MAC key is: %d\n", keycode);
	return (OK);
}

int		keyrelease(int keycode, t_data *data)
{
	//ft_printf("unpressed ");
	//ft_printf("LIN key is: %d\n", keycode);
	if (LINUX)
		linux_mac_keycode(&keycode);
	if (keycode < 280)
		data->keys[keycode] = 0;
	//show_key(data);
	//ft_printf("MAC key is: %d\n", keycode);
	return (OK);
}

//int		load_text(it_data *data, )

int		main(int argc, char **argv)
{
	int		ret_code;
	t_data	*data;

	if ((ret_code = init(argc, argv, &data)) != OK)
		print_errors(ret_code, &data);
	if (!(data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, data->mlx.mlx_wid,
		data->mlx.mlx_hei, "Cub3d")))
		print_errors(ERR_MLX_INIT, &data);
	mlx_mouse_hide(data->mlx.mlx, data->mlx.mlx_win);
	// add hook of keypress here
	//load_text(data);
	mlx_hook(data->mlx.mlx_win, 2, 1L<<0, keypress, data);
	mlx_hook(data->mlx.mlx_win, 3, 1L<<1, keyrelease, data);
	//mlx_hook(data->mlx.mlx_win, 3, 1L<<1, clp, data); //exit with esc & free
	// till here

	create_image(data);
	mlx_loop_hook(data->mlx.mlx, player_movements, data);
	mlx_loop(data->mlx.mlx);
	free_data(&data);
	ft_printf("DONE\n");
}

#include "srcs/cub3d.h"
#include "mlx.h"
#include "player_mov.h"
#include <stdio.h>
#include <math.h>

#define mapWidth 24
#define mapHeight 24

//this has to be in the Makefile only if at 42
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

void			draw_vert(t_img **img, int x, int drawStart, t_data *data, int drawEnd, int color)
{
	int y;

	y =  drawStart - 1;
	while (++y < drawEnd)
		(*img)->addr[y * data->mlx.mlx_wid + x] = color;
}

void	ray(t_data *data, t_img **img)
{
	char **worldMap = data->map;
	double posX = data->player.x, posY = data->player.y;  //x and y start position

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

	/*
		int ea_color = 0x00FF0000;
		int we_color = 0x0000FF00;
		int no_color = 0x000000FF;
		int so_color = 0x00FFFF66;
		// TODO add color stuff here!
	if (side == 0 && rayDirX > 0) // east
		draw_vert(img, x, drawStart, data, drawEnd, ea_color);
	else if (side == 0 && rayDirX < 0) // west
		draw_vert(img, x, drawStart, data, drawEnd, we_color);
	else if (side == 1 && rayDirY > 0) // south
		draw_vert(img, x, drawStart, data, drawEnd, so_color);
	else // north
		draw_vert(img, x, drawStart, data, drawEnd, no_color);
	//printf("x %d pX %f pY %f\n", x, rayDirX, rayDirY);
	*/
	double wallX; //where exactly the wall was hit
      if (side == 0) wallX = posY + perpWallDist * rayDirY;
      else           wallX = posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(texWidth));
      if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
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

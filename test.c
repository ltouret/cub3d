#include "srcs/cub3d.h"
#include "mlx.h"
#include "bmp.h"
#include "player_mov.h"
#include <stdio.h>
#include <math.h>

void			draw_vert(t_img **img, int x, int drawStart, t_data *data, int drawEnd, int color)
{
	int y;

	y =  drawStart - 1;
	while (++y < drawEnd)
		(*img)->addr[y * data->mlx.mlx_wid + x] = color;
}

void	ray(t_data *data, t_img **img)
{
	double posX = data->player.x, posY = data->player.y;  //x and y start position

	int x;
	int h;
	int w;

	x = 0;
	h = data->mlx.mlx_hei;
	w = data->mlx.mlx_wid;

	//wall casting
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

	/* COLOR MODE
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

	if (side == 0 && rayDirX > 0) // east
		data->mlx.chosen_text = &data->mlx.ea_text;
	else if (side == 0 && rayDirX < 0) // west
		data->mlx.chosen_text = &data->mlx.we_text;
	else if (side == 1 && rayDirY > 0) // south
		data->mlx.chosen_text = &data->mlx.so_text;
	else // north
		data->mlx.chosen_text = &data->mlx.no_text;

	double wallX; //where exactly the wall was hit
      if (side == 0) wallX = posY + perpWallDist * rayDirY;
      else           wallX = posX + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(data->mlx.chosen_text->wid));
      if(side == 0 && rayDirX > 0) texX = data->mlx.chosen_text->wid - texX - 1;
      if(side == 1 && rayDirY < 0) texX = data->mlx.chosen_text->wid - texX - 1;

	double step = 1.0 * data->mlx.chosen_text->wid / lineHeight;
	double tex_pos = (drawStart - data->mlx.mlx_hei
			/ 2 + lineHeight / 2) * step;
	int y = drawStart;
	data->mlx.sp_stc.z_buffer[x] = perpWallDist;
	while (y < drawEnd)
	{
		int tex_y = (int)tex_pos & (data->mlx.chosen_text->hei - 1);
		tex_pos += step;
		int color = data->mlx.chosen_text->addr[data->mlx.chosen_text->wid * tex_y + texX];
		(*img)->addr[y * data->mlx.mlx_wid + x] = color;
		y++;
	}
		x++;
	}

	// sprite casting
	int i;

	i = 0;
	while (i < data->mlx.sp_stc.sprite_num)
	{
		data->mlx.sp_stc.sprite_ord[i] = i;
		data->mlx.sp_stc.sprite_cords[i][2] = ((posX - data->mlx.sp_stc.sprite_cords[i][0])
		* (posX - data->mlx.sp_stc.sprite_cords[i][0])
		+ (posY - data->mlx.sp_stc.sprite_cords[i][1])
		* (posY - data->mlx.sp_stc.sprite_cords[i][1]));
		i++;
	}

	sort_sprites(data);
	i = 0;
	while (i < data->mlx.sp_stc.sprite_num)
	{
		//translate sprite position to relative to camera
      double spriteX = data->mlx.sp_stc.sprite_cords[data->mlx.sp_stc.sprite_ord[i]][0] - posX;
      double spriteY = data->mlx.sp_stc.sprite_cords[data->mlx.sp_stc.sprite_ord[i]][1] - posY;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      double invDet = 1.0 / (data->player.plane_x * data->player.dir_y - data->player.dir_x * data->player.plane_y); //required for correct matrix multiplication

      double transformX = invDet * (data->player.dir_y * spriteX - data->player.dir_x * spriteY);
      double transformY = invDet * (-data->player.plane_y * spriteX + data->player.plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

      int spriteScreenX = (int)((w / 2) * (1 + transformX / transformY));

	  #define uDiv 1
      #define vDiv 1
      #define vMove 0.0
      int vMoveScreen = (int)(vMove / transformY);

      //calculate height of the sprite on screen
      int spriteHeight = abs((int)(h / (transformY))) / vDiv; //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + h / 2 + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + h / 2 + vMoveScreen;
      if(drawEndY >= h) drawEndY = h - 1;

      //calculate width of the sprite
      int spriteWidth = abs( (int) (h / (transformY))) / uDiv;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= w) drawEndX = w - 1;

	  int stripe = drawStartX;
	  while (stripe < drawEndX)
	  {
		int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * data->mlx.sp_stc.sp_text.wid / spriteWidth) / 256;
		if(transformY > 0 && stripe > 0 && stripe < w && transformY < data->mlx.sp_stc.z_buffer[stripe])
		{
			int y = drawStartY;
			while (y < drawEndY)
			{
				int d = (y) * 256 - h * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
          		int texY = ((d * data->mlx.sp_stc.sp_text.hei) / spriteHeight) / 256;
				int color = data->mlx.sp_stc.sp_text.addr[data->mlx.sp_stc.sp_text.wid * texY + texX];
				if ((color & 0x00FFFFFF) != 0)
					(*img)->addr[y * data->mlx.mlx_wid + stripe] = color;
				y++;
			}
		}
		stripe++;
	  }
	  i++;
	}
}

int		main(int argc, char **argv)
{
	int		ret_code;
	t_data	*data;

	if ((ret_code = init(argc, argv, &data)) != OK)
		print_errors(ret_code);
	if (argc == 3)
	{
		if ((ret_code = save_bmp(data)) != OK)
			print_errors(ret_code);
		exit_pro();
	}
	else
	{
		if (!(data->mlx.mlx_win = mlx_new_window(data->mlx.mlx, data->mlx.mlx_wid,
			data->mlx.mlx_hei, "Cub3d")))
			print_errors(ERR_MLX_INIT);
		mlx_mouse_hide(data->mlx.mlx, data->mlx.mlx_win);
		mlx_hook(data->mlx.mlx_win, 2, 1L<<0, keypress, data);
		mlx_hook(data->mlx.mlx_win, 3, 1L<<1, keyrelease, data);
		mlx_hook(data->mlx.mlx_win, 17, 1L<<17, exit_pro, data);
		create_image(data);
		mlx_loop_hook(data->mlx.mlx, player_movements, data);
		mlx_loop(data->mlx.mlx);
	}
}

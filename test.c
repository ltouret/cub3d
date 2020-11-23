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
	//double posX = data->player.x, posY = data->player.y;  //x and y start position

	int		x;
	int		map_cords[2];
	double	ray_dirs[2];
	double	camera_x;

	x = 0;

	//wall casting
	while (x < data->mlx.mlx_wid)
	{
		//calculate ray position and direction
		camera_x = 2 * x / (double)data->mlx.mlx_wid - 1; //x-coordinate in camera space
		ray_dirs[0] = data->player.dir_x + data->player.plane_x * camera_x;
		ray_dirs[1] = data->player.dir_y + data->player.plane_y * camera_x;
		//double rayDirX = data->player.dir_x + data->player.plane_x * camera_x;
		//double rayDirY = data->player.dir_y + data->player.plane_y * camera_x;

		map_cords[0] = (int)data->player.x;
		map_cords[1] = (int)data->player.y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;
		
		 //length of ray from one x or y-side to next x or y-side
		double perpWallDist;
		
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;
		
		//int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		if (ray_dirs[0] < 0)
		{
		  stepX = -1;
		  sideDistX = (data->player.x - map_cords[0]) * (fabs(1 / ray_dirs[0]));
		}
		else
		{
		  stepX = 1;
		  sideDistX = (map_cords[0] + 1.0 - data->player.x) * (fabs(1 / ray_dirs[0]));
		}
		if (ray_dirs[1] < 0)
		{
		  stepY = -1;
		  sideDistY = (data->player.y - map_cords[1]) * (fabs(1 / ray_dirs[1]));
		}
		else
		{
		  stepY = 1;
		  sideDistY = (map_cords[1] + 1.0 - data->player.y) * (fabs(1 / ray_dirs[1]));
		}

		//perform DDA
		while (1)
		{
		  //jump to next map square, OR in x-direction, OR in y-direction
		  if (sideDistX < sideDistY)
		  {
		    sideDistX += (fabs(1 / ray_dirs[0]));
		    map_cords[0] += stepX;
		    side = 0;
		  }
		  else
		  {
		    sideDistY +=  (fabs(1 / ray_dirs[1]));
		    map_cords[1] += stepY;
		    side = 1;
		  }
		  //Check if ray has hit a wall
		   if (data->map[map_cords[1]][map_cords[0]] == '1')
			   break;
				//hit = 1;
		} 
		if (side == 0)
			perpWallDist = (map_cords[0] - data->player.x + (1 - stepX) / 2) / ray_dirs[0];
      else
		  perpWallDist = (map_cords[1] - data->player.y + (1 - stepY) / 2) / ray_dirs[1];

		int lineHeight = (int)(data->mlx.mlx_hei / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + data->mlx.mlx_hei / 2;
      if(drawStart < 0)
		  drawStart = 0;
      int drawEnd = lineHeight / 2 + data->mlx.mlx_hei / 2;
      if (drawEnd >= data->mlx.mlx_hei)
		  drawEnd = data->mlx.mlx_hei - 1;

	if (side == 0 && ray_dirs[0] > 0) // east
		data->mlx.chosen_text = &data->mlx.ea_text;
	else if (side == 0 && ray_dirs[0] < 0) // west
		data->mlx.chosen_text = &data->mlx.we_text;
	else if (side == 1 && ray_dirs[1] > 0) // south
		data->mlx.chosen_text = &data->mlx.so_text;
	else // north
		data->mlx.chosen_text = &data->mlx.no_text;

	double wallX; //where exactly the wall was hit
      if (side == 0)
		  wallX = data->player.y + perpWallDist * ray_dirs[1];
      else
		  wallX = data->player.x + perpWallDist * ray_dirs[0];
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)(data->mlx.chosen_text->wid));
      if(side == 0 && ray_dirs[0] > 0)
		  texX = data->mlx.chosen_text->wid - texX - 1;
      if(side == 1 && ray_dirs[1] < 0)
		  texX = data->mlx.chosen_text->wid - texX - 1;

	//double step = 1.0 * data->mlx.chosen_text->wid / lineHeight;
	double tex_pos = (drawStart - data->mlx.mlx_hei
			/ 2 + lineHeight / 2) * 1.0 * data->mlx.chosen_text->wid
			/ lineHeight;
	int y = drawStart;
	data->mlx.sp_stc.z_buffer[x] = perpWallDist;

	while (y < drawEnd)
	{
		int tex_y = (int)tex_pos & (data->mlx.chosen_text->hei - 1);
		tex_pos += 1.0 * data->mlx.chosen_text->wid / lineHeight;
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
		data->mlx.sp_stc.sprite_cords[i][2] = ((data->player.x - data->mlx.sp_stc.sprite_cords[i][0])
		* (data->player.x - data->mlx.sp_stc.sprite_cords[i][0])
		+ (data->player.y - data->mlx.sp_stc.sprite_cords[i][1])
		* (data->player.y - data->mlx.sp_stc.sprite_cords[i][1]));
		i++;
	}

	sort_sprites(data);
	i = 0;
	while (i < data->mlx.sp_stc.sprite_num)
	{
		//translate sprite position to relative to camera
      double spriteX = data->mlx.sp_stc.sprite_cords[data->mlx.sp_stc.sprite_ord[i]][0] - data->player.x;
      double spriteY = data->mlx.sp_stc.sprite_cords[data->mlx.sp_stc.sprite_ord[i]][1] - data->player.y;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      double invDet = 1.0 / (data->player.plane_x * data->player.dir_y - data->player.dir_x * data->player.plane_y); //required for correct matrix multiplication

      double transformX = invDet * (data->player.dir_y * spriteX - data->player.dir_x * spriteY);
      double transformY = invDet * (-data->player.plane_y * spriteX + data->player.plane_x * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

      int spriteScreenX = (int)((data->mlx.mlx_wid / 2) * (1 + transformX / transformY));

	  #define uDiv 1
      #define vDiv 1
      #define vMove 0.0
      int vMoveScreen = (int)(vMove / transformY);

      //calculate height of the sprite on screen
      int spriteHeight = abs((int)(data->mlx.mlx_hei / (transformY))) / vDiv; //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + data->mlx.mlx_hei / 2 + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + data->mlx.mlx_hei / 2 + vMoveScreen;
      if(drawEndY >= data->mlx.mlx_hei) drawEndY = data->mlx.mlx_hei - 1;

      //calculate width of the sprite
      int spriteWidth = abs( (int) (data->mlx.mlx_hei / (transformY))) / uDiv;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= data->mlx.mlx_wid) drawEndX = data->mlx.mlx_wid - 1;

	  int stripe = drawStartX;
	  while (stripe < drawEndX)
	  {
		int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * data->mlx.sp_stc.sp_text.wid / spriteWidth) / 256;
		if(transformY > 0 && stripe > 0 && stripe < data->mlx.mlx_wid && transformY < data->mlx.sp_stc.z_buffer[stripe])
		{
			int y = drawStartY;
			while (y < drawEndY)
			{
				int d = (y) * 256 - data->mlx.mlx_hei * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
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

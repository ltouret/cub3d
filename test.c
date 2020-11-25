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
	int		side; //was a NS or a EW wall hit?
	double	perpWallDist;

	//wall casting
	x = 0;
	while (x < data->mlx.mlx_wid)
	{
		data->mlx.ray_dirs[0] = data->player.dir_x + data->player.plane_x * (2 * x / (double)data->mlx.mlx_wid - 1);
		data->mlx.ray_dirs[1] = data->player.dir_y + data->player.plane_y * (2 * x / (double)data->mlx.mlx_wid - 1);
		data->mlx.map_cords[0] = (int)data->player.x;
		data->mlx.map_cords[1] = (int)data->player.y;
		wall_casting(data);
		wall_casting2(data, &side);
		wall_casting3(data, side, &perpWallDist);
		wall_casting4(data, side, perpWallDist, x, img);
		data->mlx.sp_stc.z_buffer[x] = perpWallDist;
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

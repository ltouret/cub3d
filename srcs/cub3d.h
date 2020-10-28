/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 02:08:41 by ltouret           #+#    #+#             */
/*   Updated: 2020/10/28 19:48:32 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"

# define ERR 0
# define OK 1
# define ERR_RES 2
# define ERR_TEXT 3
# define ERR_COLOR 4
# define ERR_INV_COLOR 5 // use this if > 255
# define ERR_MAP_NOT_LAST 6
# define ERR_DUP_MAP 7
# define ERR_INV_MAP 8 
# define ERR_MANY_PLAYER 11
# define ERR_DUP_KEY 13
# define ERR_INV_KEY 14
# define ERR_MAL 21
# define ERR_UK 28 
# define ERR_FEW_ARG 30
# define ERR_MANY_ARG 31
# define ERR_INV_ARG 32
# define ERR_NO_FILE 34 // case file doenst exist 
# define ERR_INV_FILE_NAME 35 // case file no .cub

# define ERR_MISS_MAP 40 
# define ERR_MISS_NO 41
# define ERR_MISS_SO 42
# define ERR_MISS_EA 43
# define ERR_MISS_WE 44
# define ERR_MISS_C 45
# define ERR_MISS_F 46
# define ERR_MISS_S 47
# define ERR_MISS_R 48
# define ERR_MISS_PLA 49

# define ERR_MLX_INIT 51
# define ERR_MLX 52
# define ERR_WRI_BMP 53

typedef struct		s_ok_map
{
	int				r;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				s;
	int				f;
	int				c;
	int				map_sta;
	int				map_end;
	int				player;
}					t_ok_map;

typedef struct		s_text_img
{
	int				wid;
	int				hei;
	int				bpp;
	int				size;
	int				endian;
	void			*img;
	int				*addr;
}					t_text_img;

typedef struct		s_sprite
{
	int				sprite_num;
	int				*sprite_ord;
	double			**sprite_cords;
	double			*z_buffer;
	t_text_img		sp_text;
}					t_sprite;

typedef struct		s_mlx
{
	void			*mlx;
	void			*mlx_win;
	long			mlx_wid;
	long			mlx_hei;
	t_text_img		no_text;
	t_text_img		so_text;
	t_text_img		ea_text;
	t_text_img		we_text;
	t_sprite		sp_stc;
	t_text_img		*chosen_text;
}					t_mlx;

typedef struct		s_text_path
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sp;
}					t_text_path;

typedef struct		s_color
{
	int				f_color;
	int				c_color;
}					t_color;

typedef struct		s_player
{
	double			x;
	double			y;
	char			ori;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			rot_speed;
	double			mov_speed;
	int				radius;
}					t_player;

typedef struct		s_img
{
	void			*img;
	int				*addr;
	int				bpp;
	int				line_length;
	int				endian;
}					t_img;

typedef struct		s_data //check for missing data
{
	t_mlx			mlx;
	t_text_path		text_path;
	t_color			color;
	t_player		player;
	int				map_width;
	int				map_height;
	int				keys[280];
	char			**map;
}					t_data;

void	init_t_map(t_ok_map *map);
void	init_data(t_data *data);
int		missing_data(t_ok_map *map);
int		check_res(char *line);
int		get_reso(int *map_res, char *line, t_data *data);
int		check_text(char *path);
int		get_text(int *map_text, char *line, char **data_text);
int		free_tab(char **tab, int index);
int		check_color(char *tmp);
int		get_color(int *map_bool, char *line, int *data_color);
int		check_map(char *line, t_ok_map *map);
int		map_start(char *line);
int		get_map(t_ok_map *map, char *line, t_data *data);
int		check_dup(t_ok_map *map, char *line);
int		parsing2(t_ok_map *map, char *line, t_data *data);
int		parsing(t_ok_map *map, char *line, t_data *data);
int		read_file(int fd, t_ok_map *map, t_data *data);
int		check_file_typ(char *filename);
int		open_fd(char *filename);
int		handle_args(int argc, char **argv);
int		validate_map(t_data *data);
void	handle_player(t_data *data, char *map_line);
int		add_data(t_data *data);
void	retrieve_sprite(t_data *data, char *map_line);
int		init_sprite(t_data *data);
int		init(int argc, char **argv, t_data **data);
void	free_data(t_data **data);
void	print_errors(int err_code);
void	ray(t_data *data, t_img **img);
void	draw_vert(t_img **img, int x, int drawStart, t_data *data, int drawEnd, int color);
void	draw_floor_ceil(t_data *data, t_img **img);
double	degreeToRadians(double degree);
int		create_image(t_data *data);
int		fill_image(t_data *data, t_img **img);
int		keyrelease(int keycode, t_data *data);
int		keypress(int keycode, t_data *data);
int		player_movements(t_data *data);
void	sort_sprites(t_data *data);
int		exit_pro(void);

#endif

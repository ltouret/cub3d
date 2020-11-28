/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 02:08:41 by ltouret           #+#    #+#             */
/*   Updated: 2020/11/28 18:04:26 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include "error.h"

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
	int				sprite_screen;
	int				sprite_hei;
	int				sprite_wid;
	int				draw_y[2];
	int				draw_x[2];
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
	int				map_cords[2];
	int				steps[2];
	double			wall_dist;
	double			side_dists[2];
	double			ray_dirs[2];
	int				draw_wall[2];
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

typedef struct		s_data
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

int					missing_data(t_ok_map *map);
int					check_res(char *line);
int					get_reso(int *map_res, char *line, t_data *data);
int					check_text(char *path);
int					get_text(int *map_text, char *line, char **data_text);
int					free_tab(char **tab, int index);
int					check_color(char *tmp);
int					get_color(int *map_bool, char *line, int *data_color);
int					check_map(char *line, t_ok_map *map);
int					map_start(char *line);
int					get_map(t_ok_map *map, char *line, t_data *data);
int					check_dup(t_ok_map *map, char *line);
int					parsing2(t_ok_map *map, char *line, t_data *data);
int					parsing(t_ok_map *map, char *line, t_data *data);
int					read_file(int fd, t_ok_map *map, t_data *data);
int					check_file_typ(char *filename);
int					open_fd(char *filename);
int					validate_map(t_data *data);
void				handle_player(t_data *data, char *map_line);
int					add_data(t_data *data);
void				retrieve_sprite(t_data *data, char *map_line);
int					init_sprite(t_data *data);
int					init(int argc, char **argv, t_data **data);
void				init_player(t_data *data);
void				print_errors(int err_code);
int					create_image(t_data *data);
int					fill_image(t_data *data, t_img **img);
void				wall_casting(t_data *data);
void				wall_casting2(t_data *data, int *side);
void				wall_casting3(t_data *data, int side);
void				wall_casting4(t_data *data, int side, int x, t_img **img);
double				wall_casting5(t_data *data, int side, int *tex_cords);
void				sprite_casting(t_data *data);
void				sprite_casting1(t_data *data, int i, double *sprite_cam,
				double *trans_cords);
void				sprite_casting2(t_data *data, double *trans_cords);
void				sprite_casting3(t_data *data, double *trans_cords,
				t_img **img);
void				sprite_casting4(t_data *data, int tex_x, t_img **img);
int					keyrelease(int keycode, t_data *data);
int					keypress(int keycode, t_data *data);
int					player_movements(t_data *data);
void				sort_sprites(t_data *data);
int					exit_pro(void);

#endif

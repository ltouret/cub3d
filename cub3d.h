/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 02:08:41 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/03 00:37:27 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h> // include only in file that needs this shit -- open 

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
//# define ERR_MISSING_ELEM
# define ERR_DUP_KEY 13
# define ERR_INV_KEY 14
# define ERR_MAL 21
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

typedef struct		s_data // add map data
{
	int				width;
	int				height;
	char			*no_text;
	char			*so_text;
	char			*we_text;
	char			*ea_text;
	char			*s_text;
	char			*f_color;
	char			*c_color;
	char			**map;
}					t_data;
#endif

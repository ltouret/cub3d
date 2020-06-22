/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 02:08:41 by ltouret           #+#    #+#             */
/*   Updated: 2020/06/22 19:12:14 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>

# define ERR 0
# define OK 1
# define ERR_RES 2
# define ERR_TEXT 3
# define ERR_COLOR 4
# define ERR_W_COLOR 5 // use this if > 255
//# define ERR_MISSING_ELEM
# define ERR_INV_KEY 14
# define ERR_MAL 21

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
	int				map;
}					t_ok_map;

typedef struct		s_data
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
}					t_data;
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 15:24:57 by ltouret           #+#    #+#             */
/*   Updated: 2020/10/28 19:52:54 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	max_len_map(char **map)
{
	int		i;
	int		len;
	int		tmp_len;

	i = 0;
	len = 0;
	while (map[i])
	{
		if ((tmp_len = ft_strlen(map[i])) > len)
			len = tmp_len;
		i++;
	}
	return (len);
}

static int	add_space_map(char **map)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = max_len_map(map);
	while (map[i])
	{
		if (ft_strlen(map[i]) < len)
		{
			if (!(tmp = malloc(sizeof(char) * (len + 1))))
				return (ERR_MAL);
			ft_strlcpy(tmp, map[i], len);
			ft_memset(tmp + ft_strlen(tmp), ' ', len - ft_strlen(tmp));
			tmp[len] = '\0';
			free(map[i]);
			map[i] = tmp;
		}
		i++;
	}
	return (OK);
}

static int	check_cloture(char **map, int x, int y)
{
	if (!(x - 1 >= 0 && y - 1 >= 0 && map[y - 1][x - 1] != ' '))
		return (ERR_INV_MAP);
	if (!(x >= 0 && y - 1 >= 0 && map[y - 1][x] != ' '))
		return (ERR_INV_MAP);
	if (!(x + 1 >= 0 && y - 1 >= 0 && map[y - 1][x + 1] != ' '))
		return (ERR_INV_MAP);
	if (!(x - 1 >= 0 && y >= 0 && map[y][x - 1] != ' '))
		return (ERR_INV_MAP);
	if (!(x + 1 >= 0 && y >= 0 && map[y][x + 1] != ' '))
		return (ERR_INV_MAP);
	if (!(x - 1 >= 0 && y + 1 >= 0 && map[y + 1][x - 1] != ' '))
		return (ERR_INV_MAP);
	if (!(x >= 0 && y + 1 >= 0 && map[y + 1][x] != ' '))
		return (ERR_INV_MAP);
	if (!(x + 1 >= 0 && y + 1 >= 0 && map[y + 1][x + 1] != ' '))
		return (ERR_INV_MAP);
	return (OK);
}

static int	map_len(t_data *data)
{
	data->map_width = ft_strlen(data->map[0]);
	if (init_sprite(data) == ERR_MAL)
		return (ERR_MAL);
	data->mlx.sp_stc.sprite_num = 0;
	while (data->map[data->map_height])
	{
		handle_player(data, data->map[data->map_height]);
		retrieve_sprite(data, data->map[data->map_height]);
		data->map_height++;
	}
	return (OK);
}

int			validate_map(t_data *data)
{
	int		x;
	int		y;

	if (add_space_map(data->map) == ERR_MAL)
		return (ERR_MAL);
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (ft_strchr("02NSWE", data->map[y][x]))
			{
				if (check_cloture(data->map, x, y) == ERR_INV_MAP)
					return (ERR_INV_MAP);
				if (data->map[y][x] == '2')
					data->mlx.sp_stc.sprite_num++;
			}
			x++;
		}
		y++;
	}
	if (map_len(data) == ERR_MAL)
		return (ERR_MAL);
	return (OK);
}

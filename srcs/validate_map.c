/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 15:24:57 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/11 00:24:31 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//TODO ERASE print_map

void	print_map(char **map)
{
	int		i;

	i = 0;
	ft_printf("Parsed map is:\n");
	while (map[i])
		ft_printf("%s\n", map[i++]);
}

int		max_len_map(char **map)
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

int		add_space_map(char **map)
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

int		check_cloture(char **map, int x, int y)
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

int		validate_map(char **map)
{
	int		x;
	int		y;

	if (add_space_map(map) == ERR_MAL)
		return (ERR_MAL);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (ft_strchr("02NSWE", map[y][x]))
			{
				if (check_cloture(map, x, y) == ERR_INV_MAP)
					return (ERR_INV_MAP);
			}
			x++;
		}
		y++;
	}
	return (OK);
}

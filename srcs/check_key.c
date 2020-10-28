/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:59:06 by ltouret           #+#    #+#             */
/*   Updated: 2020/10/28 19:49:48 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>

int		check_res(char *line)
{
	int		i;

	i = 1;
	while (line[i])
	{
		if (line[i] != ' ' && ft_isdigit(line[i]) == 0)
			return (ERR_RES);
		i++;
	}
	return (OK);
}

int		check_text(char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (ERR_TEXT);
	close(fd);
	return (OK);
}

int		check_color(char *tmp)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		if (ft_isdigit(tmp[i]) == 0)
			return (ERR_COLOR);
		i++;
	}
	return (OK);
}

int		check_map(char *line, t_ok_map *map)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("012NSWE ", line[i]))
			return (ERR_INV_MAP);
		if (ft_strchr("NSWE", line[i]))
		{
			if (map->player == 0)
				map->player = 1;
			else
				return (ERR_MANY_PLAYER);
		}
		i++;
	}
	map->map_sta = 1;
	return (OK);
}

int		check_dup(t_ok_map *map, char *line)
{
	int		ret_code;

	ret_code = OK;
	if (!ft_strncmp(line, "R ", 2) && map->r == 1)
		ret_code = ERR_DUP_KEY;
	else if (!ft_strncmp(line, "NO ", 3) && map->no == 1)
		ret_code = ERR_DUP_KEY;
	else if (!ft_strncmp(line, "SO ", 3) && map->so == 1)
		ret_code = ERR_DUP_KEY;
	else if (!ft_strncmp(line, "WE ", 3) && map->we == 1)
		ret_code = ERR_DUP_KEY;
	else if (!ft_strncmp(line, "EA ", 3) && map->ea == 1)
		ret_code = ERR_DUP_KEY;
	else if (!ft_strncmp(line, "S ", 2) && map->s == 1)
		ret_code = ERR_DUP_KEY;
	else if (!ft_strncmp(line, "F ", 2) && map->f == 1)
		ret_code = ERR_DUP_KEY;
	else if (!ft_strncmp(line, "C ", 2) && map->c == 1)
		ret_code = ERR_DUP_KEY;
	if (ret_code != OK)
		free(line);
	return (ret_code);
}

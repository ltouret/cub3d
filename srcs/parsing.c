/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:30:27 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/10 23:11:32 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parsing2(t_ok_map *map, char *line, t_data *data)
{
	int		ret_code;

	ret_code = 0;
	if (!ft_strncmp(line, "C ", 2) && map->c == 0 && map->map_sta == 0)
		ret_code = get_color(&map->c, line, &data->c_color);
	else if (map_start(line) == OK && map->map_end != 1)
		ret_code = get_map(map, line, data);
	else if (map->map_end == 1 && map_start(line))
		ret_code = ERR_DUP_MAP;
	else if (map->map_end == 1 && line[0] != '\0')
		ret_code = ERR_MAP_NOT_LAST;
	else if (line[0] == '\0')
		ret_code = OK;
	else
		ret_code = ERR_INV_KEY;
	return (ret_code);
}

int		parsing(t_ok_map *map, char *line, t_data *data)
{
	int		ret_code;

	ret_code = 0;
	if (map->map_sta == 1 && map_start(line) != OK)
		map->map_end = 1;
	if (!ft_strncmp(line, "R ", 2) && map->r == 0 && map->map_sta == 0)
		ret_code = get_reso(&map->r, line, data);
	else if (!ft_strncmp(line, "NO ", 3) && map->no == 0 && map->map_sta == 0)
		ret_code = get_text(&map->no, line, &data->no_text);
	else if (!ft_strncmp(line, "SO ", 3) && map->so == 0 && map->map_sta == 0)
		ret_code = get_text(&map->so, line, &data->so_text);
	else if (!ft_strncmp(line, "WE ", 3) && map->we == 0 && map->map_sta == 0)
		ret_code = get_text(&map->we, line, &data->we_text);
	else if (!ft_strncmp(line, "EA ", 3) && map->ea == 0 && map->map_sta == 0)
		ret_code = get_text(&map->ea, line, &data->ea_text);
	else if (!ft_strncmp(line, "S ", 2) && map->s == 0 && map->map_sta == 0)
		ret_code = get_text(&map->s, line, &data->s_text);
	else if (!ft_strncmp(line, "F ", 2) && map->f == 0 && map->map_sta == 0)
		ret_code = get_color(&map->f, line, &data->f_color);
	else
		ret_code = parsing2(map, line, data);
	return (ret_code);
}
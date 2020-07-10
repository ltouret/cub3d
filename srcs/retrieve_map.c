/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 20:04:56 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/10 23:23:24 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map_start(char *line)
{
	int		i;
	int		ret_code;

	i = 0;
	ret_code = ERR;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		ret_code = OK;
	return (ret_code);
}

int		get_map(t_ok_map *map, char *line, t_data *data)
{
	int		i;
	char	**tmp;

	if ((i = check_map(line, map)) != OK)
		return (i);
	if (!data->map)
	{
		if (!(data->map = malloc(sizeof(char *) * 1)))
			return (ERR_MAL);
		data->map[0] = NULL;
	}
	i = 0;
	while (data->map[i])
		i++;
	if (!(tmp = malloc(sizeof(char *) * (i + 2))))
		return (ERR_MAL);
	i = -1;
	while (data->map[++i])
		tmp[i] = data->map[i];
	if (!(tmp[i] = ft_strdup(line)))
		return (ERR_MAL);
	tmp[i + 1] = NULL;
	free(data->map);
	data->map = tmp;
	return (OK);
}

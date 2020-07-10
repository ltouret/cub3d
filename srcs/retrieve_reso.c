/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_reso.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 18:09:33 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/10 23:23:35 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		num_len(int num)
{
	int		i;

	i = 0;
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

int				get_reso(int *map_res, char *line, t_data *data)
{
	int		i;

	if (check_res(line) == ERR_RES)
		return (ERR_RES);
	i = 1;
	while (line[i] == ' ')
		i++;
	data->width = ft_atoi(line + i);
	i += num_len(data->width);
	while (line[i] == ' ')
		i++;
	data->height = ft_atoi(line + i);
	i += num_len(data->height);
	if (!(line[i] == '\0' && data->height > 0 && data->width > 0))
		return (ERR_RES);
	*map_res = 1;
	return (OK);
}

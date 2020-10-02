/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 00:34:19 by ltouret           #+#    #+#             */
/*   Updated: 2020/10/02 17:11:41 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_player(t_data *data, char *map_line)
{
	int i;

	i = 0;
	while (map_line[i])
	{
		if (ft_find("NWSE", map_line[i]) != -1)
		{
			if (map_line[i] == 'N' || map_line[i] == 'S')
			{
				data->player.dir_y = (map_line[i] == 'N') ? -1 : 1;
				data->player.plane_x = 0.66;
			}
			else if (map_line[i] == 'W' || map_line[i] == 'E')
			{
				data->player.dir_x = (map_line[i] == 'W') ? -1 : 1;
				data->player.plane_y = 0.66;
			}
			data->player.x = i + 0.5;
			data->player.y = data->map_height + 0.5;
			data->player.ori = map_line[i];
			map_line[i] = '0';
		}
		i++;
	}
}

//static	int	add_text(t_data);

int		add_data(t_data *data)
{
	int		ret_code;

	if ((ret_code = validate_map(data)) != OK)
		return (ret_code);
	return (OK);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 00:34:19 by ltouret           #+#    #+#             */
/*   Updated: 2020/08/01 03:30:52 by ltouret          ###   ########.fr       */
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
			if (map_line[i] == 'N')
				data->player.ori = 0;
			else if (map_line[i] == 'W')
				data->player.ori = 270;
			else if (map_line[i] == 'S')
				data->player.ori = 180;
			else if (map_line[i] == 'E')
				data->player.ori = 90;
			data->player.x = i;
			data->player.y = data->map_height;
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
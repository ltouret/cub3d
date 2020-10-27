/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 18:07:27 by ltouret           #+#    #+#             */
/*   Updated: 2020/10/27 23:19:12 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		cast_color(char **tab, int *data_color, int *map_bool)
{
	int		i;

	i = -1;
	while (tab[++i])
	{
		if (check_color(tab[i]) == ERR_COLOR && free_tab(tab, 3))
			return (ERR_COLOR);
		if (ft_atoi(tab[i]) > 255 && free_tab(tab, 3))
			return (ERR_INV_COLOR);
	}
	*data_color = ((ft_atoi(tab[0]) << 16) + (ft_atoi(tab[1]) << 8) +
		ft_atoi(tab[2]));
	free_tab(tab, 3);
	*map_bool = 1;
	return (OK);
}

static int		count_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int				get_color(int *map_bool, char *line, int *data_color)
{
	int		i;
	char	*tmp;
	char	**tab;

	if (!(tab = ft_split(line + 1, ',')))
		return (ERR_MAL);
	if (count_tab(tab) != 3)
	{
		free_tab(tab, 0);
		return (ERR_COLOR);
	}
	i = -1;
	while (tab[++i])
	{
		if (!(tmp = ft_strtrim(tab[i], " ")))
		{
			free_tab(tab, 3);
			return (ERR_MAL);
		}
		free(tab[i]);
		tab[i] = tmp;
	}
	return (cast_color(tab, data_color, map_bool));
}

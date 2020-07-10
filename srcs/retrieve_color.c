/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 18:07:27 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/10 23:23:16 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		write_color(char **str, int num)
{
	char	*tmp;

	free(*str);
	if (num < 16)
	{
		tmp = ft_itoa_base(num, "0123456789abcdef");
		*str = ft_strjoin("0", tmp);
		free(tmp);
	}
	else
		*str = ft_itoa_base(num, "0123456789abcdef");
	if (*str == NULL)
		return (ERR_MAL);
	return (OK);
}

int		cast_color(char **tab, char **data_color, int *map_bool)
{
	int		i;
	char	*tmp;

	i = -1;
	while (tab[++i])
	{
		if (check_color(tab[i]) == ERR_COLOR && free_tab(tab, 3))
			return (ERR_COLOR);
		if (ft_atoi(tab[i]) > 255 && free_tab(tab, 3))
			return (ERR_INV_COLOR);
		if (write_color(&tab[i], ft_atoi(tab[i])) == ERR_MAL &&
			free_tab(tab, 3))
			return (ERR_MAL);
	}
	tmp = ft_strjoin(tab[0], tab[1]);
	*data_color = ft_strjoin(tmp, tab[2]);
	free(tmp);
	free_tab(tab, 3);
	if (*data_color == NULL)
		return (ERR_MAL);
	*map_bool = 1;
	return (OK);
}

int		count_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		get_color(int *map_bool, char *line, char **data_color)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 18:11:23 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/10 23:23:44 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_text(int *map_text, char *line, char **data_text)
{
	int		i;

	i = 2;
	while (line[i] == ' ')
		i++;
	if (check_text(line + i) == ERR_TEXT)
		return (ERR_TEXT);
	if (!(*data_text = ft_strdup(line + i)))
		return (ERR_MAL);
	*map_text = 1;
	return (OK);
}

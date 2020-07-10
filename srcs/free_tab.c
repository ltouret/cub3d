/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 15:30:47 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/10 22:57:57 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		free_tab(char **tab, int index)
{
	int		i;

	if (tab == NULL)
		return (OK);
	i = 0;
	if (index == 0)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	else
	{
		while (i < index)
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
	return (OK);
}

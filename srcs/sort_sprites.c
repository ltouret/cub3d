/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:39:16 by ltouret           #+#    #+#             */
/*   Updated: 2020/10/28 19:42:13 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void swap(int* xp, int* yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void	sort_sprites(t_data *data) 
{
    int i;
	int j;
	double **arr;
  
	arr = data->mlx.sp_stc.sprite_cords;
	i = 0;
	while (i < data->mlx.sp_stc.sprite_num - 1)
	{
		j = 0; 
		while (j < data->mlx.sp_stc.sprite_num - i - 1)
		{
			if (arr[data->mlx.sp_stc.sprite_ord[j]][2]
			< arr[data->mlx.sp_stc.sprite_ord[j + 1]][2])
			swap(&data->mlx.sp_stc.sprite_ord[j],
		&data->mlx.sp_stc.sprite_ord[j + 1]);
			j++;
		}
		i++;
	}
}

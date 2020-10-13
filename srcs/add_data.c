/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 00:34:19 by ltouret           #+#    #+#             */
/*   Updated: 2020/10/14 00:33:01 by ltouret          ###   ########.fr       */
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

int		load_text(t_data *data, t_text_img *text_img, char *text_path)
{
	if (!(text_img->img = mlx_xpm_file_to_image(data->mlx.mlx, text_path,
		&text_img->wid, &text_img->hei)))
		return (ERR_MLX);
	if (!(text_img->addr = (int *)mlx_get_data_addr(text_img->img, &text_img->bpp,
		&text_img->size, &text_img->endian)))
		return (ERR_MLX);
	return (OK);
}

int		add_data(t_data *data)
{
	int		ret_code;

	if ((ret_code = load_text(data, &data->mlx.no_text, data->text_path.no))
		!= OK)
		return (ret_code);
	if ((ret_code = load_text(data, &data->mlx.so_text, data->text_path.so))
		!= OK)
		return (ret_code);
	if ((ret_code = load_text(data, &data->mlx.ea_text, data->text_path.ea))
		!= OK)
		return (ret_code);
	if ((ret_code = load_text(data, &data->mlx.we_text, data->text_path.we))
		!= OK)
		return (ret_code);
	if ((ret_code = load_text(data, &data->mlx.sp_text, data->text_path.sp))
		!= OK)
		return (ret_code);
	if ((ret_code = validate_map(data)) != OK)
		return (ret_code);
	return (OK);
}

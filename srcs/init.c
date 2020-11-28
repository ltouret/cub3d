/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:51:31 by ltouret           #+#    #+#             */
/*   Updated: 2020/11/28 17:50:12 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_t_map(t_ok_map *map)
{
	map->r = 0;
	map->no = 0;
	map->so = 0;
	map->we = 0;
	map->ea = 0;
	map->s = 0;
	map->f = 0;
	map->c = 0;
	map->player = 0;
	map->map_sta = 0;
	map->map_end = 0;
}

static void	init_data(t_data *data)
{
	int i;

	i = -1;
	while (++i < 280)
		data->keys[i] = 0;
	data->map_width = 0;
	data->map_height = 0;
	data->map = NULL;
	data->mlx.mlx = NULL;
	data->mlx.mlx_win = NULL;
	data->text_path.no = NULL;
	data->text_path.so = NULL;
	data->text_path.ea = NULL;
	data->text_path.we = NULL;
	data->text_path.sp = NULL;
	data->color.f_color = 0;
	data->color.c_color = 0;
	data->mlx.sp_stc.sprite_num = 0;
	init_player(data);
}

int			missing_data(t_ok_map *map)
{
	if (map->r == 0)
		return (ERR_MISS_R);
	if (map->no == 0)
		return (ERR_MISS_NO);
	if (map->so == 0)
		return (ERR_MISS_SO);
	if (map->we == 0)
		return (ERR_MISS_WE);
	if (map->ea == 0)
		return (ERR_MISS_EA);
	if (map->s == 0)
		return (ERR_MISS_S);
	if (map->f == 0)
		return (ERR_MISS_F);
	if (map->c == 0)
		return (ERR_MISS_C);
	if (map->map_sta == 0)
		return (ERR_MISS_MAP);
	if (map->player == 0)
		return (ERR_MISS_PLA);
	return (OK);
}

static int	handle_args(int argc, char **argv)
{
	if (argc < 2)
		return (ERR_FEW_ARG);
	else if (argc > 3)
		return (ERR_MANY_ARG);
	if (argc == 3 && ft_strcmp("--save", argv[2]) != 0)
		return (ERR_INV_ARG);
	return (OK);
}

int			init(int argc, char **argv, t_data **data)
{
	t_ok_map	map;
	int			fd;
	int			ret_code;

	*data = NULL;
	if ((ret_code = handle_args(argc, argv)) != OK)
		return (ret_code);
	if ((ret_code = check_file_typ(argv[1])) != OK)
		return (ret_code);
	if (!(*data = malloc(sizeof(t_data))))
		return (ERR_MAL);
	init_t_map(&map);
	init_data(*data);
	if (!((*data)->mlx.mlx = mlx_init()))
		return (ERR_MLX_INIT);
	fd = open_fd(argv[1]);
	if ((ret_code = fd) == ERR_NO_FILE)
		return (ret_code);
	if ((ret_code = read_file(fd, &map, *data)) != OK)
		return (ret_code);
	close(fd);
	if ((ret_code = add_data(*data)) != OK)
		return (ret_code);
	return (OK);
}

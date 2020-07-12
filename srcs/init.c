/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 17:51:31 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/12 10:44:38 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_t_map(t_ok_map *map)
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

void	init_data(t_data *data)
{
	data->width = 0;
	data->height = 0;
	data->no_text = NULL;
	data->so_text = NULL;
	data->ea_text = NULL;
	data->we_text = NULL;
	data->s_text = NULL;
	data->f_color = NULL;
	data->c_color = NULL;
	data->map = NULL;
}

int		missing_data(t_ok_map *map)
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

int		handle_args(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf("not enough args\n");
		return (ERR_FEW_ARG);
	}
	else if (argc > 3)
	{
		ft_printf("too many args\n");
		return (ERR_MANY_ARG);
	}
	if (argc == 3 && ft_strcmp("--save", argv[2]) != 0)
	{
		ft_printf("wrong second arg not --save\n");
		return (ERR_INV_ARG);
	}
	return (OK);
}

//TODO remove printfs, and create func that prints error msgs!
int		init(int argc, char **argv, t_data **data)
{
	t_ok_map	map;
	int			fd;
	int			ret_code;

	*data = NULL;
	if ((ret_code = handle_args(argc, argv)) != OK)
		return (ret_code);
	if ((ret_code = check_file_typ(argv[1])) != OK)
		return (ret_code);
	fd = open_fd(argv[1]);
	if ((ret_code = fd) == ERR_NO_FILE)
		return (ret_code);
	if (!(*data = malloc(sizeof(t_data))))
		return (ERR_MAL);
	init_t_map(&map);
	init_data(*data);
	if ((ret_code = read_file(fd, &map, *data)) != OK)
		return (ret_code);
	close(fd);
	if ((ret_code = validate_map((*data)->map)) != OK)
		return (ret_code);
	return (OK);
}

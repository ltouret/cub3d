/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:30:27 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/01 20:52:01 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
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

int		num_len(int num)
{
	int		i;

	i = 0;
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

int		check_res(char *line)
{
	int		i;

	i = 1;
	while (line[i])
	{
		if (line[i] != ' ' && ft_isdigit(line[i]) == 0)
			return (ERR_RES);
		i++;
	}
	return (OK);
}

int		get_reso(int *map_res, char *line, t_data *data)
{
	int		i;

	if (!check_res(line) == ERR_RES)
		return (ERR_RES);
	i = 1;
	while (line[i] == ' ')
		i++;
	data->width = ft_atoi(line + i);
	i += num_len(data->width);
	while (line[i] == ' ')
		i++;
	data->height = ft_atoi(line + i);
	i += num_len(data->height);
	if (!(line[i] == '\0' && data->height > 0 && data->width > 0))
		return (ERR_RES);
	*map_res = 1;
	return (OK);
}

int		check_text(char *path)
{
	int		fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (ERR_TEXT);
	return (OK);
}

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

int		check_color(char *tmp)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		if (ft_isdigit(tmp[i]) == 0)
			return (ERR_COLOR);
		i++;
	}
	return (OK);
}

int		write_color(char **str, int num)
{
	char	*tmp;
	int		ret_code;

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

int		check_map(char *line, t_ok_map *map)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("012NSWE ", line[i]))
			return (ERR_INV_MAP);
		if (ft_strchr("NSWE", line[i]))
		{
			if (map->player == 0)
				map->player = 1;
			else
				return (ERR_MANY_PLAYER);
		}
		i++;
	}
	map->map_sta = 1;
	return (OK);
}

int		map_start(char *line)
{
	int		i;
	int		ret_code;

	i = 0;
	ret_code = ERR;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		ret_code = OK;
	return (ret_code);
}

int		get_map(t_ok_map *map, char *line, t_data *data)
{
	int		i;
	char	**tmp;

	if ((i = check_map(line, map)) != OK)
		return (i);
	if (!data->map)
	{
		if (!(data->map = malloc(sizeof(char *) * 1)))
			return (ERR_MAL);
		data->map[0] = NULL;
	}
	i = 0;
	while (data->map[i])
		i++;
	if (!(tmp = malloc(sizeof(char *) * (i + 2))))
		return (ERR_MAL);
	i = -1;
	while (data->map[++i])
		tmp[i] = data->map[i];
	if (!(tmp[i] = ft_strdup(line)))
		return (ERR_MAL);
	tmp[i + 1] = NULL;
	free(data->map);
	data->map = tmp;
	return (OK);
}

int		check_dup(t_ok_map *map, char *line)
{
	int		ret_code;

	ret_code = OK;
	if (!ft_strncmp(line, "R ", 2) && map->r == 1)
		ret_code = ERR_DUP_KEY;
	else if (!ft_strncmp(line, "NO ", 3) && map->no == 1)
		ret_code = ERR_DUP_KEY;
	else if (!ft_strncmp(line, "SO ", 3) && map->so == 1)
		ret_code = ERR_DUP_KEY;
	else if (!ft_strncmp(line, "WE ", 3) && map->we == 1)
		ret_code = ERR_DUP_KEY;
	else if (!ft_strncmp(line, "EA ", 3) && map->ea == 1)
		ret_code = ERR_DUP_KEY;
	else if (!ft_strncmp(line, "S ", 2) && map->s == 1)
		ret_code = ERR_DUP_KEY;
	else if (!ft_strncmp(line, "F ", 2) && map->f == 1)
		ret_code = ERR_DUP_KEY;
	else if (!ft_strncmp(line, "C ", 2) && map->c == 1)
		ret_code = ERR_DUP_KEY;
	return (ret_code);
}

int		parsing2(t_ok_map *map, char *line, t_data *data)
{
	int		ret_code;

	ret_code = 0;
	if (!ft_strncmp(line, "C ", 2) && map->c == 0 && map->map_sta == 0)
		ret_code = get_color(&map->c, line, &data->c_color);
	else if (map_start(line) == OK && map->map_end != 1)
		ret_code = get_map(map, line, data);
	else if (map->map_end == 1 && line[0] != '\0')
		ret_code = ERR_MAP_NOT_LAST;
	else if (line[0] == '\0')
	{
		ret_code = OK;
		if (map->map_sta == 1)
			map->map_end = 1;
	}
	else
		ret_code = ERR_INV_KEY;
	return (ret_code);
}

// TODO how to handle case that map starts with 0? send error now or later with check mvalid map?
int		parsing(t_ok_map *map, char *line, t_data *data)
{
	int		ret_code;

	ret_code = 0;
	if (check_dup(map, line) == ERR_DUP_KEY)
	{
		ft_printf("ret of line: %d\n", ERR_DUP_KEY);
		return (ERR_DUP_KEY);
	}
	if (!ft_strncmp(line, "R ", 2) && map->r == 0 && map->map_sta == 0)
		ret_code = get_reso(&map->r, line, data);
	else if (!ft_strncmp(line, "NO ", 3) && map->no == 0 && map->map_sta == 0)
		ret_code = get_text(&map->no, line, &data->no_text);
	else if (!ft_strncmp(line, "SO ", 3) && map->so == 0 && map->map_sta == 0)
		ret_code = get_text(&map->so, line, &data->so_text);
	else if (!ft_strncmp(line, "WE ", 3) && map->we == 0 && map->map_sta == 0)
		ret_code = get_text(&map->we, line, &data->we_text);
	else if (!ft_strncmp(line, "EA ", 3) && map->ea == 0 && map->map_sta == 0)
		ret_code = get_text(&map->ea, line, &data->ea_text);
	else if (!ft_strncmp(line, "S ", 2) && map->s == 0 && map->map_sta == 0)
		ret_code = get_text(&map->s, line, &data->s_text);
	else if (!ft_strncmp(line, "F ", 2) && map->f == 0 && map->map_sta == 0)
		ret_code = get_color(&map->f, line, &data->f_color);
	else
		ret_code = parsing2(map, line, data);
	return (ret_code);
}

int		read_file(int fd, t_ok_map *map, t_data *data)
{
	int		gnl;
	int		ret_code;
	char	*line;

	gnl = 1;
	while (gnl == 1)
	{
		gnl = get_next_line(fd, &line);
		ft_printf("%s\n", line);
		if ((ret_code = parsing(map, line, data)) != OK)
		{
			free(line);
			ft_printf("%d\n", ret_code);
			return (ret_code);
		}
		free(line);
	}
	if ((ret_code = missing_data(map)) != OK)
	{
		ft_printf("%d\n", ret_code);
		return (ret_code);
	}
	/*
	ft_printf("Parsed map is:\n");
	while (data->map[gnl])
	{
		ft_printf("%s\n", data->map[gnl++]);
	}
	*/
}

int		check_file_typ(char *filename)
{
	int		i;

	i = ft_strlen(filename) - 4;
	if (filename[i] == '.')
	{
		i++;
		if (filename[i] == 'c')
		{
			i++;
			if (filename[i] == 'u')
			{
				i++;
				if (filename[i] == 'b')
				{
					return (OK);
				}
			}
		}
	}
	ft_printf("wrong file name\n");
	return (ERR_INV_FILE_NAME);
}

int		open_fd(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ERR_NO_FILE);
	return (fd);
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
int		main(int argc, char **argv)
{
	t_ok_map	*map;
	t_data		*data;
	int			fd;
	int			ret_code;

	if ((ret_code = handle_args(argc, argv)) != OK)
		return (ret_code);
	if ((ret_code = check_file_typ(argv[1])) == ERR_INV_FILE_NAME)
		return (ret_code);
	fd = open_fd(argv[1]);
	if ((ret_code = fd) == ERR_NO_FILE)
	{
		ft_printf("no file\n");
		return (ret_code);
	}

	if (!(map = malloc(sizeof(t_ok_map))))
		return (0);
	if (!(data = malloc(sizeof(t_data))))
		return (0);
	init_t_map(map);
	init_data(data);
	read_file(fd, map, data);
	ft_printf("file closed %d\n", close(fd));

	// create free func later
	free(map);
	free(data->no_text);
	free(data->we_text);
	free(data->ea_text);
	free(data->so_text);
	free(data->s_text);
	free(data->f_color);
	free(data->c_color);
	free_tab(data->map, 0);
	free(data);
	return (0);
}

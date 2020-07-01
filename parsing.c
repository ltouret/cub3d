/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:30:27 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/01 01:56:54 by ltouret          ###   ########.fr       */
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
	map->map = 0;
	map->map_sta = 0;
	//ft_printf("init done\n");
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
}

int		num_len(int num)
{
	int i;

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
	int i;

	i = 1;
	while(line[i])
	{
		if (line[i] != ' ' && ft_isdigit(line[i]) == 0)
			return (ERR_RES);
		i++;
	}
	return (OK);
}

int		get_reso(int *map_res, char *line, t_data *data) // re code split!
{
	int		i;

	//add check_res func here! if works keep goind else stop return bad reso
	if (!check_res(line) == ERR_RES)
		return (ERR_RES); // return Error\n invalid resolution
	i = 1;
	while (line[i] == ' ')
		i++;
	data->width = ft_atoi(line + i);
	i += num_len(data->width);
	while (line[i] == ' ')
		i++;
	data->height = ft_atoi(line + i);
	i += num_len(data->height);
	//ft_printf("wid %d - hei %d\n", data->width, data->height);
	if (!(line[i] == '\0' && data->height > 0 && data->width > 0))// add return with ERR res incorrect MAYBE MOT NEEDED THE \0
		return (ERR_RES);
	//ft_printf("good res\n");
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

int	free_tab(char **tab, int index)
{
	int i;

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

int		check_color(char *tmp) //try this pro more
{
	int i;

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

void	ft_free(const char *str, ...) // try and do a multiple param free?
{
}

int		cast_color(char **tab, char **data_color, int *map_bool)
//TODO add usage of ERR_INV_COLOR if > 255
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
		if (write_color(&tab[i], ft_atoi(tab[i])) == ERR_MAL && free_tab(tab, 3))
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

int		map_last(t_ok_map *map)
// checks if map is the last element of the file
// this shit is worng!
{
	if (map->r && map->no && map->so && map->we && map->ea && map->s && map->f
		&& map->c)
		return (OK);
	ft_printf("map not last!\n");
	return (ERR); // return error of ERR_MAP_NOT_LAST
}

int		check_map(char *line, t_ok_map *map)
{
	int		i;
	
	i = 0;
	if (line[i])
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
	}
	map->map_sta = 1;
	return (OK);
}

int		map_start(char *line)
//TODO check the return code of this. seems fishy
{
	int		i;
	int		ret_code;

	i = 0;
	ret_code = ERR;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1')
		ret_code = OK;
	return (ret_code);
}

int		get_map(t_ok_map *map, char *line, t_data *data)
{
	int		i;
	char	**tmp;

	if (i = check_map(line, map) != OK)
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

int		parsing(t_ok_map *map, char *line, t_data *data) //change ret vals to actual func
// TODO fix, this shit is brojken if no space in between key and value
{
	int ret_code; // this func will get the ret of the other func and handle if error

	ret_code = 0;
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
	else if (!ft_strncmp(line, "C ", 2) && map->c == 0 && map->map_sta == 0)
		ret_code = get_color(&map->c, line, &data->c_color);
	else if (map_start(line) == OK) //in case of map add if only at the end of file!!!!!
		ret_code = get_map(map, line, data); // call map func here
	else if (map->map_sta == 1 && line[0] != '\0')
		ret_code = 11;
	else if (line[0] == '\0') // in case of empty line in the file
		ret_code = OK;
	else
		ret_code = ERR_INV_KEY;
	ft_printf("ret of line: %d\n", ret_code);
	return (ret_code);
}

int		read_file(int fd, t_ok_map *map, t_data *data) // uncomment to use ft_split
{
	int		gnl;
	char	*line;
	//char **arr;

	//int i = 0;

	line = NULL;
	gnl = 1;
	//while ((gnl = get_next_line(fd, &line)) > 0)
	while (gnl == 1)
	{
		gnl = get_next_line(fd, &line);
		//arr = ft_split(line + 1, ' ');
		//line = ft_strtrim(line, "\f\t \n\r\v"); //trim or not trim spaces?
		ft_printf("%s\n", line);
		parsing(map, line, data);
		free(line);
		/*while (arr[i] != NULL)
		{
			ft_printf("%s\n", arr[i]);
			free(arr[i]);
			i++;
		}
		free(arr);
		gnl = 0;*/
	}
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
		return (ERR_NO_FILE); // return 
	return (fd);
}

int		handle_args(int argc, char **argv)
//TODO keep argv[1] (filename) in memory in struct
// handle that the argv[2] must be "--save" with strcmp.
{
	if (argc < 2)
	{
		ft_printf("not enough args\n");
		return (ERR_FEW_ARG); // change TOO FEW ARGS
	}
	else if (argc > 3)
	{
		ft_printf("too many args\n"); // change TOO MANY ARGS
		return (ERR_MANY_ARG);
	}
	if (argc == 3 && ft_strcmp("--save", argv[2]) != 0)
	{
		ft_printf("wrong 2second arg not --save\n");
		return (ERR_INV_ARG);
	}
	return (OK);
}

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
		return (ret_code); // return ERR_NO_FILE
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

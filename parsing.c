/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:30:27 by ltouret           #+#    #+#             */
/*   Updated: 2020/06/20 21:00:46 by ltouret          ###   ########.fr       */
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
	map->map = 0;
	ft_printf("init done\n");
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
	ft_printf("wid %d - hei %d\n", data->width, data->height);
	if (!(line[i] == '\0' && data->height > 0 && data->width > 0))// add return with ERR res incorrect
		return (ERR_RES);
	ft_printf("good res\n");
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
//TODO check if need to create another error for sprite of s sprite
{
	int		i;

	if (check_text(line) == ERR_TEXT)
		return (ERR_TEXT); 
	i = 2;
	while (line[i] == ' ')
		i++;
	if (!(*data_text = ft_strdup(line + i)))
		return (ERR_MAL);
	*map_text = 1;
	ft_printf("good text %d %s\n", *map_text, *data_text);
	return (OK);
}

int		check_color(char *line) // erase if not used!!!
{
	int i;

	i = 1;
	while(line[i])
	{
		if (line[i] != ' ' && ft_isdigit(line[i]) == 0 && line[i] != ',')
			return (ERR_F);
		i++;
	}
	return (OK);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int		check_num_color(char *tmp) //try this pro more
{
	int i;

	i = 0;
	ft_printf("trying: %s\n", tmp);
	while (tmp[i])
	{
		if (ft_isdigit(tmp[i]) == 0)
		{
			ft_printf("its a '%c'\n", tmp[i]);
			return (ERR_F);
		}
		i++;
	}
	return (OK);
}

int		cast_color(char **tab, char **data_color)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i])
	// malloc pro
	// try and use num var instead of 100+ atois
	// 255 10 0 should be ff0a00 --> add 0 if only one digit
	{
		tmp = ft_strtrim(tab[i], " ");
		if (check_num_color(tmp) == ERR_F || ft_atoi(tmp) > 255 ) // call free func here
		{
			free_tab(tab);
			free(tmp);
			return (ERR_F);
		}
		free(tab[i]);
		if (ft_atoi(tmp) == 0)
			tab[i] = ft_strdup("00");
		else
			tab[i] = ft_itoa_base(ft_atoi(tmp), "0123456789abcdef");
		ft_printf("%s %s\n", tmp, tab[i]);
		free(tmp);
		i++;
	}
	tmp = ft_strjoin(tab[0], tab[1]);
	*data_color = ft_strjoin(tmp, tab[2]);
	ft_printf("%s %s\n", tmp, *data_color);
	free (tmp);
	free_tab(tab);
}

int		get_color(int *map_bool, char *line, char **data_color)
// TODO rename all map to bool
// malloc protection
{
	int		i;
	char	**tab;

	tab = ft_split(line + 1, ','); // & here
	i = 0;
	while (tab[i])
		i++;
	ft_printf("len of list: %d\n", i);
	if (i != 3) // free everything in tab b4 get this out of here // call free func here
	{
		free_tab(tab);
		return (ERR_F);
	}
	return (cast_color(tab, data_color));
}

int		parsing(t_ok_map *map, char *line, t_data *data) //change ret vals to actual func
// TODO fix, this shit is brojken if no space in between key and value
{
	int ret_code; // this func will get the ret of the other func and handle if error
	// TODO change all return to ret_code

	ret_code = 0;
	if (!ft_strncmp(line, "R ", 2) && map->r == 0)
		ret_code = get_reso(&map->r, line, data);
	else if (!ft_strncmp(line, "NO ", 3) && map->no == 0)
		ret_code = get_text(&map->no, line, &data->no_text);
	else if (!ft_strncmp(line, "SO ", 3) && map->so == 0)
		ret_code = get_text(&map->so, line, &data->so_text);
	else if (!ft_strncmp(line, "WE ", 3) && map->we == 0)
		ret_code = get_text(&map->we, line, &data->we_text);
	else if (!ft_strncmp(line, "EA ", 3) && map->ea == 0)
		ret_code = get_text(&map->ea, line, &data->ea_text);
	else if (!ft_strncmp(line, "S ", 2) && map->s == 0)
		ret_code = get_text(&map->s, line, &data->s_text);
	else if (!ft_strncmp(line, "F ", 2) && map->f == 0)
		ret_code = get_color(&map->f, line, &data->f_color);
	else if (!ft_strncmp(line, "C ", 2)&& map->c == 0)
		ret_code = OK; // get color here
	else if(line[0] == ' ' || line[0] == ' ') // in case of empty line in the file
		ret_code = OK; // call map func here
	else if(line[0] == '\0') // in case of empty line in the file
		ret_code = OK;
	else
		ret_code = ERR_INV_KEY;
	//ft_printf("ret of line: %d\n", ret_code);
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

int		main(int argc, char **argv)
{
	t_ok_map	*map;
	t_data		*data;
	int			fd;

	if (!(map = malloc(sizeof(t_ok_map))))
		return (0);
	if (!(data = malloc(sizeof(t_data))))
		return (0);

	//fd = open("maps/map.cub", O_RDONLY);
	fd = open("maps/file.cub", O_RDONLY);
	//fd = open("maps/file_error.cub", O_RDONLY);
	if (fd == -1)
	{
		// call error func for frees here
		free(map);
		return (0); // return ERR_FILE_DOESN_EXIST
	}
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
	free(data);
	return (0);
}

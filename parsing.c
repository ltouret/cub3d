/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:30:27 by ltouret           #+#    #+#             */
/*   Updated: 2020/06/16 19:00:37 by ltouret          ###   ########.fr       */
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

int		check_res(char *line, t_data *data)
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
	if (!check_res(line, data) == ERR_RES)
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
{
	int		i;

	if (check_text(line) == ERR_TEXT)
		return (ERR_TEXT); 
	i = 2;
	while (line[i] == ' ')
		i++;
	*data_text = ft_strdup(line + i);
	*map_text = 1;
	ft_printf("good text %d %s\n", *map_text, *data_text);
	return (OK);
}

int		get_color(int *map_bool, char *line, char **data_color) // TODO rename all map to bool
{
	int		i;
	char	*tmp;
	char	**tmp2;

	i = 0;
	tmp = ft_strtrim(line + 1, " ");
	tmp2 = ft_split(tmp, ',');
	ft_printf("%s\n", tmp);
	while (tmp2[i])
	{
		ft_printf("%s\n", ft_strtrim(tmp2[i], " "));
		free(tmp2[i]);
		i++;
	}
	free(tmp2);
	free(tmp);
}

int		parsing(t_ok_map *map, char *line, t_data *data) //change ret vals to actual func
// TODO fix, this shit is brojken if no space in between key and value
{
	if (!ft_strncmp(line, "R ", 2) && map->r == 0)
		return (get_reso(&map->r, line, data));
	else if (!ft_strncmp(line, "NO ", 3) && map->no == 0)
		return (get_text(&map->no, line, &data->no_text));
	else if (!ft_strncmp(line, "SO ", 3) && map->so == 0)
		return (get_text(&map->so, line, &data->so_text));
	else if (!ft_strncmp(line, "WE ", 3) && map->we == 0)
		return (get_text(&map->we, line, &data->we_text));
	else if (!ft_strncmp(line, "EA ", 3) && map->ea == 0)
		return (get_text(&map->ea, line, &data->ea_text));
	else if (!ft_strncmp(line, "S ", 2) && map->s == 0)
		return (get_text(&map->s, line, &data->s_text));
	else if (!ft_strncmp(line, "F ", 2) && map->f == 0)
		return (get_color(&map->f, line, &data->f_color));
	else if (!ft_strncmp(line, "C ", 2)&& map->c == 0)
		return (1);
	else if(line[0] == '\n')
		return (1);
	
	//ft_printf("%d\n", ft_strncmp(line, "NO", 2));
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

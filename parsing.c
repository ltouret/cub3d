/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 22:30:27 by ltouret           #+#    #+#             */
/*   Updated: 2020/06/13 23:18:21 by ltouret          ###   ########.fr       */
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
	ft_printf("init done\n");
}

int		missing_data(t_ok_map *map)
{
}

int		get_reso(t_ok_map *map, char *line) // re code split!
{
	/*int i;
	int len;

	i = 1;
	len = 0;
	while (ft_find("\f\t \n\r\v", line[i]) != -1)
		i++;
	ft_printf("%s\n", line + i);
	len = ft_strlen(ft_itoa(ft_atoi(line + i)));
	i += len;
	ft_printf("%d\n", len);
	while (ft_find("\f\t \n\r\v", line[i]) != -1)
		i++;
	ft_printf("%s\n", line  + i);*/
	return (1);
}

int		parsing(t_ok_map *map, char *line) //change ret vals to actual func
{
	if (line[0] == 'R' && map->r == 0)
		return (get_reso(map, line));
	else if (!ft_strncmp(line, "NO", 2) && map->no == 0)
		return (1);
	else if (!ft_strncmp(line, "SO", 2) && map->no == 0)
		return (1);
	else if (!ft_strncmp(line, "WE", 2) && map->no == 0)
		return (1);
	else if (!ft_strncmp(line, "EA", 2) && map->no == 0)
		return (1);
	else if (line[0] == 'F' && map->f == 0)
		return (1);
	else if (line[0] == 'C' && map->c == 0)
		return (1);
	//ft_printf("%d\n", ft_strncmp(line, "NO", 2));
}

int		read_file(int fd, t_ok_map *map) // uncomment to use ft_split
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
		parsing(map, line);
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
	int		fd;

	if (!(map = malloc(sizeof(t_ok_map))))
		return (0);

	fd = open("maps/map.cub", O_RDONLY);
	if (fd == -1)
	{
		// call error func for frees here
		free(map);
		return (0); // return ERR_FILE_DOESN_EXIST
	}
	init_t_map(map);
	read_file(fd, map);
	ft_printf("file closed %d\n", close(fd));
	free(map);
	return (0);
}

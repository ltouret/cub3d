/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouret <ltouret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 15:36:49 by ltouret           #+#    #+#             */
/*   Updated: 2020/07/10 23:14:47 by ltouret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		read_file(int fd, t_ok_map *map, t_data *data)
{
	int		gnl;
	int		ret_code;
	char	*line;

	gnl = 1;
	while (gnl == 1)
	{
		gnl = get_next_line(fd, &line);
		//ft_printf("%s\n", line);
		if (check_dup(map, line) == ERR_DUP_KEY)
		{
			ft_printf("ret of line: %d\n", ERR_DUP_KEY);
			return (ERR_DUP_KEY);
		}
		if ((ret_code = parsing(map, line, data)) != OK)
		{
			free(line);
			ft_printf("%d\n", ret_code);
			return (ret_code);
		}
		//ft_printf("ret: %d\n", ret_code);
		free(line);
	}
	if ((ret_code = missing_data(map)) != OK)
	{
		ft_printf("%d\n", ret_code);
		return (ret_code);
	}
	//print_map(data->map);
	add_space_map(&data->map);
	//ft_printf("\n");
	//print_map(data->map);
	return (OK);
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

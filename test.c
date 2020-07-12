#include "srcs/cub3d.h"

void	free_data(t_data **data)
{
	if (*data == NULL)
		return ;
	free((*data)->no_text);
	free((*data)->we_text);
	free((*data)->ea_text);
	free((*data)->so_text);
	free((*data)->s_text);
	free((*data)->f_color);
	free((*data)->c_color);
	free_tab((*data)->map, 0);
	free(*data);
	*data = NULL;
}

void	err_msgs2(char *err[100])
{
	err[30] = "Too few arguments provided";
	err[31] = "Too many arguments provided";
	err[32] = "Invalid argument provided";
	err[34] = "Invalid map file path";
	err[35] = "Invalid map file name";
	err[40] = "Missing map";
	err[41] = "Missing north texture";
	err[42] = "Missing south texture";
	err[43] = "Missing east texture";
	err[44] = "Missing west texture";
	err[45] = "Missing ceiling color";
	err[46] = "Missing floor color";
	err[47] = "Missing sprite texture";
	err[48] = "Missing resolution";
	err[49] = "Missing player in map";
}

// TODO change err tab to real number
void	error_msgs(int err_code, char *err[100])
{
	int		i;

	i = 0;
	while (i < 100)
		err[i++] = "Unknown error";
	if (err_code < 30)
	{
		err[2] = "Invalid resolution";
		err[3] = "Invalid texture path";
		err[4] = "Invalid color";
		err[5] = "Invalid color value";
		err[6] = "Map is not last";
		err[7] = "Duplicate map";
		err[8] = "Invalid map";
		err[11] = "Too many players";
		err[13] = "Duplicate key in map";
		err[14] = "Invalid key in map";
		err[21] = "Malloc error";
		err[28] = "Unknown error";
	}
	else
		err_msgs2(err);
	//err[] = "";
}

void	print_errors(int err_code, t_data **data)
{
	char	*err[100];

	if (err_code < 0 || err_code > 100)
		err_code = ERR_UK;
	error_msgs(err_code, err);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err[err_code], 2);
	ft_putstr_fd("\n", 2);
	free_data(data);
	exit (-1);
}

int		main(int argc, char **argv)
{
	int		ret_code;
	t_data	*data;

	if ((ret_code = init(argc, argv, &data)) != OK)
		print_errors(ret_code, &data);
	free_data(&data);
	ft_printf("DONE\n");
}

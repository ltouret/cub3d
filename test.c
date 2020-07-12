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
}

int		main(int argc, char **argv)
{
	int		ret_code;
	t_data	*data;
	
	data = NULL;
	if ((ret_code = init(argc, argv, &data)) != OK)
		ft_printf("Error from init is: %d\n", ret_code);
	free_data(&data);
	ft_printf("DONE\n");
}

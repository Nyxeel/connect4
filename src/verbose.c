
#include "../inc/connect4.h"

void	print_map(t_data *data)
{
	int i = 0;
	while (data->map[i])
	{
		ft_printf("%s\n", data->map[i]);
		i++;
	}
	return ;
}
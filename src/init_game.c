
#include "connect4.h"

bool	init_game(t_data *data)
{
	srand(time(NULL));
	init_signals();

	data->map = ft_calloc(data->rows + 1, sizeof(char *));
	if (!data->map)
		return (false);

	int i = 0;
	while (i < data->rows)
	{
		data->map[i] = ft_calloc(data->columns + 1, sizeof(char));
		if (!data->map[i])
		{
			free_split(data->map);
			return (false);
		}
		int j = 0;
		while (j < data->columns)
		{
			data->map[i][j] = '0';
			j++;
		}
		i++;
	}

	if (VERBOSE)
	{
		print_map(data);
	}
	return (true);
}
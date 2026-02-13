
#include "connect4.h"

static bool	digit_check(const char *str)
{
	ft_skip_zeros(&str);
	ft_skip_signs(&str);
	int j = 0;
	while (str[j])
	{
		if (!ft_isdigit(str[j++]))
			return (false);
	}
	return true;
}

static bool	init_game(t_data *data)
{
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

static bool	parse(t_data *data, char **argv)
{
	if (!digit_check(argv[1]) || !digit_check(argv[2]))
	{
		print_error("Only numbers are valid!");
		return (false);
	}
	if (int_overflow_check(argv[1]) || int_overflow_check(argv[2]))
	{
		print_error("Number overflowed");
		return (false);
	}
	if (((data->rows = atoi(argv[1])) <= 0) || ((data->columns = atoi(argv[2])) <= 0))
	{
		print_error("Negative numbers are not allowed");
		return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_data data;

	if (ac != 3 || !av[1] || !av[2])
		return (print_error("FAILED to load"), 0);

	if (!parse(&data, av) || init_game(&data))
		return (0);
	//start_game();
	return (0);
}
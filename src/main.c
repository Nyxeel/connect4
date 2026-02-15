
#include "../inc/connect4.h"

volatile sig_atomic_t g_signal = 0;

int	main(int ac, char **av)
{
	t_data data;

	if (ac == 4 && ft_strcmp(av[3], "bonus") == 0)
		data.flag.bonus = true;
	else if (ac != 3 || !av[1] || !av[2])
		return (print_error("Please enter exact 2 argument - first for grid rows, second for grid columns"), 0);

	if (!parse(&data, av) || !init_game(&data))
		return (ERROR);

	if (!start_game(&data))
		return (free_split(data.map), ERROR);

	free_split(data.map);
	return (SUCCESS);
}

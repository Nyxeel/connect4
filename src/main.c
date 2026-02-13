
#include "connect4.h"

volatile sig_atomic_t g_signal = 0;

int	main(int ac, char **av)
{
	t_data data;

	if (ac != 3 || !av[1] || !av[2])
		return (print_error("FAILED to load"), 0);

	if (!parse(&data, av) || !init_game(&data))
		return (ERROR);

	if (!start_game(&data))
		return (ERROR);

	return (SUCCESS);
}
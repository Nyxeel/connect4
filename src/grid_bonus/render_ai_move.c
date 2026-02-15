
#include "../../inc/connect4.h"
#include "ncurses.h"

void	render_move(t_data *data, int best_col)
{
	int x = data->drop_position;
	int y = best_col;

	int moves;
	if (x > y)
		moves = x - y;
	else
		moves = y - x;

	while (moves > 0 && data->flag.no_render == false)
	{
		if (x > y)
			data->drop_position--;
		else if (x == y)
			continue;
		else
			data->drop_position++;
		color_input(data, &data->cell);
		refresh();
		ft_sleep(1);

		moves--;
	}
	ft_sleep(1);
	refresh();
	return ;
}
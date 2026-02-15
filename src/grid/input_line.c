

#include "../../inc/connect4.h"
#include "ncurses.h"

void	color_input(t_data *data, Cell *cell)
{
	short color;

	if (data->flag.player == AI_MOVE)
		color = RED;
	else
		color = YELLOW;


	int input_y = 1;
	int start_y = 1 + input_y * (cell->h + 1);

	/// delete old input line
	for (int col = 0; col < data->columns; col++)
	{
		int start_x = 1 + col * (cell->w + 1);

		for (int row = 0; row < cell->h; row++)
		{
			move(start_y + row, start_x);
			if (start_y + row < data->terminal_max_y)
				chgat(cell->w, A_NORMAL, BLACK, NULL);
		}
	}

	// color new cell
	int x = data->drop_position;
	int start_x = 1 + x * (cell->w + 1);

	for (int row = 0; row < cell->h; row++)
	{
		move(start_y + row, start_x);
		if (start_y + row < data->terminal_max_y)
			chgat(cell->w, A_NORMAL, color, NULL);
	}
}



#include "../../inc/connect4.h"
#include "ncurses.h"


void	color_input(t_data *data, Cell *cell)
{

	int x = data->drop_position;

	int y = 1;

	int start_x = 1 + x * (cell->w + 1);
	int start_y = 1 + y * (cell->h + 1);

	short color;
	if (data->flag.player == AI_MOVE)
		color = RED;
	else
		color = YELLOW;

	for (int row = 0; row < cell->h; row++)
	{
		move(start_y + row, start_x);
		if(start_y < data->terminal_max_y)
			chgat(cell->w, A_NORMAL, color, NULL);
	}
	return ;
}


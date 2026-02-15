
#include "../../inc/connect4.h"
#include "ncurses.h"


void	reset_message_box(t_data *data, Cell *cell)
{
	attron(COLOR_PAIR(BLACK));


	int start_x;
	int start_y = 1;

	for (int i = 0; i < cell->h; i++)
	{
		start_x = 1;
		for (int row = 0; row < data->terminal_max_x; row++)
		{
			mvaddch(start_y, start_x++, ' ');
		}
		start_y++;
	}
	attroff(COLOR_PAIR(BLACK));

	return ;
}

void	message_box(t_data *data, Cell *cell, char *message)
{

	(void) cell;

	if (!message)
		return ;

	compute_cell_size(data, cell);

	int textstart = (data->terminal_max_x  / 2) - (ft_strlen(message) / 2);
	int y_center = 1 + (cell->h / 2);

	short color;
	if (data->flag.player == AI_MOVE)
		color = TEXT_RED;
	else if (data->flag.player == PLAYER_MOVE)
		color = TEXT_YELLOW;
	else
		color = TEXT_BLUE;

	//reset_message_box(data, cell);

	/// PUT NEW STRING IN MESSAGE BOX
	attron(COLOR_PAIR(color));
	move(y_center, textstart);
    printw("%s", message);
	attroff(COLOR_PAIR(color));\
	refresh();
	return ;
}




#include "../../inc/connect4.h"
#include "ncurses.h"


void	update_message_box(t_data *data, Cell *cell, char *message)
{


	int y = 10;

	int x_center = (data->columns / 2) + (cell->w / 2);
	int y_center = y + (cell->h / 2);

	short color;
	if (data->flag.player == AI_MOVE)
		color = TEXT_RED;
	else
		color = TEXT_YELLOW;

	message = ft_strdup("Your turn. Move with arrows left/right and drop pawn with 'SPACE'");

	attron(COLOR_PAIR(color));
	int textstart   = x_center - (ft_strlen(message) / 2);
			move(y_center, textstart);
                printw("%s", message);

	attroff(COLOR_PAIR(color));
	return ;
}


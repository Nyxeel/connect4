

#include "../../inc/connect4.h"
#include "ncurses.h"


void	delete_message(int x, int y, char *message)
{

	if (!message)
		return ;

	attron(COLOR_PAIR(BLACK));
	int text_len = ft_strlen(message);
	int textstart   = x - (text_len / 2);
	move(y, textstart);

	int i = 0;
	while (i < text_len )
	{
		printw(" ");
		i++;
	}
	attroff(COLOR_PAIR(BLACK));

	return ;
}

void	message_box(t_data *data, Cell *cell, char *message)
{

	(void) cell;


	int textstart   = 1;
	int y_center = (data->terminal_max_x  / 2) - ft_strlen(message);

	short color;
	if (data->flag.player == AI_MOVE)
		color = TEXT_RED;
	else
		color = TEXT_YELLOW;

	if (!message)
		message = ft_strdup("Your turn. Move with arrows left/right and drop pawn with 'SPACE'");

	delete_message(textstart, y_center, message);

	attron(COLOR_PAIR(color));

			move(y_center, textstart);
                printw("%s", message);

	attroff(COLOR_PAIR(color));
	return ;
}




#include "../../inc/connect4.h"

#include <ncurses.h>



short	get_color(char c)
{

	if (c == PLAYER_COLOR)			// PLAYER FILLS MAP WITH '2'
	{
		return YELLOW;
	}
	else if (c == AI_COLOR)			// AI FILLS MAP WITH '1'
	{
		return RED;
	}
    return BLACK;
}

int	color_game_map(t_data *data, Cell *cell, int x, int y)
{
	char map_num = data->map[y][x];
	int start_x = 1 + x * (cell->w + 1);
	int start_y = 1 + (y + 2) * (cell->h + 1);

	short color = get_color(map_num);
	for (int row = 0; row < cell->h; row++)
	{
		move(start_y + row, start_x);
		if( start_y < data->terminal_max_y)
			chgat(cell->w, A_NORMAL, color, NULL);
	}
	return (0);
}

int	color_grid(t_data *data, Cell *cell)
{

	int	x = 0;
	int y = 0;


	while (y < data->rows) // loops through each cell per col
	{
		x = 0;
		while (x < data->columns) // loops through each cell per row
		{
			if (color_game_map(data, cell, x, y))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

static void compute_cell_size(t_data *data, Cell *cell)
{

    int usable_w = data->terminal_max_x - (data->columns + 1);		//Calculate the usable width of the window for the grid.
    int usable_h = data->terminal_max_y - (data->rows + 2 + 1);		//2 extras rows for input and text output

    if (usable_w < data->columns || usable_h < data->rows + 2) // Safety check: if the usable area is smaller than the grid
    {
        cell->w = 2;
        cell->h = 1;
        return;
    }
	cell->w = usable_w / data->columns;					//calc usable cell witdh and height by dividing evenly
	cell->h = usable_h / (data->rows + 2);
	if (cell->w < 3)										//enforce minimum cellsize for cell_w and cell_h
	    cell->w = 2;
	if (cell->h < 2)
	    cell->h = 1;
}



int render_grid(t_data *data, Cell *cell)
{
    // attron(COLOR_PAIR( ENTER ));
    getmaxyx(stdscr, data->terminal_max_y, data->terminal_max_x);
	compute_cell_size(data, cell);
    clear();

	int need_w = data->columns * (cell->w + 1) + 1;
	int need_h = (data->rows + 2) * (cell->h + 1) + 1;
	if (need_w > data->terminal_max_x || need_h > data->terminal_max_y)
	{
		printw("Terminal too small! Minimum size: [%d, %d]\n", need_w, need_h);
		refresh();
		return (0);
	}

	//RENDER INPUT LINE

	if (!data->flag.start)
	{
		data->flag.start = true;    //// set back to false after chossing was successfull
		data->drop_position = data->rows/ 2;
	}
	message_box(data, &data->cell, NULL);

	color_input(data, &data->cell);

	/// RENDER GAME MAP
    int y = 2 *(cell->h + 1);
    for (int row = 2; row < data->rows + 2; row++)
    {
        int x = 0;
        for (int col = 0; col < data->columns; col++)
        {
            mvaddch(y, x++, '+');
            for (int i = 0; i < cell->w; i++)
                mvaddch(y, x++, '-');
        }
        mvaddch(y, x, '+');
        y++;

        for (int h = 0; h < cell->h; h++)
        {
            x = 0;
            for (int col = 0; col < data->columns; col++)
            {
                mvaddch(y, x++, '|');
                for (int i = 0; i < cell->w; i++){
                    mvaddch(y, x++, ' ');
				}
            }
            mvaddch(y, x, '|');
            y++;
        }
    }

    int x = 0;
    for (int col = 0; col < data->columns; col++)
    {
        mvaddch(y, x++, '+');
        for (int i = 0; i < cell->w; i++)
            mvaddch(y, x++, '-');
    }
    mvaddch(y, x, '+');

	if (color_grid(data, &data->cell))
		return (1);		// fills cells with different colors
    refresh();
	return (0);
}

bool	render_loop(t_data *game)
{
	while (1)
	{
		getmaxyx(stdscr, game->terminal_max_y, game->terminal_max_x);
        if (game->terminal_max_x < 43 || game->terminal_max_y < 17) {
            clear();
            printw("Window too small! Minimum size 17 x 43\n");
            getch();
            continue;
        }

		if (render_grid(game, &game->cell))
			return false;

		// Get user input
        int ch = getch();

		if (ch == KEY_RESIZE && game->flag.player == PLAYER_MOVE)
		{
            getmaxyx(stdscr, game->terminal_max_y, game->terminal_max_x);
            continue;
        }
		if (ch == ESC)
		{
		   endwin();
		   return false; // ESC gedrückt
		}
		if (ch == 32 && game->flag.player == PLAYER_MOVE)
		{
			//check if input is possible    // SPACE gedrückt
			return true;
		}

		if (ch == KEY_LEFT && game->flag.player == PLAYER_MOVE)
        {

			if (game->drop_position - 1 < 0)
			{
				game->drop_position = game->columns - 1;
				message_box(game, &game->cell, "Move to left not possible\n");
				refresh();
			}
			else
				game->drop_position -= 1;
            continue;
        }
		if (ch == KEY_RIGHT && game->flag.player == PLAYER_MOVE)
        {

			if (game->drop_position + 1 == game->columns)
			{
				game->drop_position = game->columns % game->columns;
				message_box(game, &game->cell, "Move to right not possible\n");
				refresh();
			}
			else
				game->drop_position += 1;
            continue;
        }


	}
	return true;
}

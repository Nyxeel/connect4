
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

int find_landing_row(t_data *data, int column)
{
    int row = data->rows - 1;
    while (row >= 0)
    {
        if (data->map[row][column] == '1' || data->map[row][column] == '2')
            row--;
        else
            return row;
    }
    return -1; // Column is full
}

void highlight_landing_cell(t_data *data, Cell *cell)
{
    if (data->flag.player != PLAYER_MOVE)
        return;
        
    int landing_row = find_landing_row(data, data->drop_position);
    if (landing_row == -1)
        return; // Column is full, don't highlight
        
    int start_x = 1 + data->drop_position * (cell->w + 1);
    int start_y = 1 + (landing_row + 2) * (cell->h + 1);
    
    // Highlight the landing cell with a distinctive appearance
    for (int row = 0; row < cell->h; row++)
    {
        move(start_y + row, start_x);
        if (start_y + row < data->terminal_max_y)
            chgat(cell->w, A_REVERSE | A_BOLD, LANDING_INDICATOR, NULL);
    }
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

void compute_cell_size(t_data *data, Cell *cell)
{
	getmaxyx(stdscr, data->terminal_max_y, data->terminal_max_x);
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


int	render_game(t_data *data, Cell *cell)
{
	/// RENDER GAME MAP
    int y = 2 *(cell->h + 1);
    for (int row = 2; row < data->rows + 2; row++)
    {
        int x = 0;
        for (int col = 0; col < data->columns; col++)
        {
            mvaddch(y, x++, ACS_PLUS);
            for (int i = 0; i < cell->w; i++)
                mvaddch(y, x++, ACS_HLINE);
        }
        mvaddch(y, x, ACS_PLUS);
        y++;

        for (int h = 0; h < cell->h; h++)
        {
            x = 0;
            for (int col = 0; col < data->columns; col++)
            {
                mvaddch(y, x++, ACS_VLINE);
                for (int i = 0; i < cell->w; i++)
                    mvaddch(y, x++, ' ');
            }
            mvaddch(y, x, ACS_VLINE);
            y++;
        }
    }

    int x = 0;
    for (int col = 0; col < data->columns; col++)
    {
        mvaddch(y, x++, ACS_PLUS);
        for (int i = 0; i < cell->w; i++)
            mvaddch(y, x++, ACS_HLINE);
    }
    mvaddch(y, x, ACS_PLUS);

  	if (color_grid(data, &data->cell))
		return (1);		// fills cells with different colors
    refresh();
	return 0;
}


int render_grid(t_data *data, Cell *cell)
{
  	compute_cell_size(data, cell);
   	int need_w = data->columns * (cell->w + 1) + 1;
	int need_h = (data->rows + 2) * (cell->h + 1) + 1;
	if (need_w > data->terminal_max_x || need_h > data->terminal_max_y)
	{
		clear();
		printw("Terminal too small! Minimum size: [%d, %d]\n", need_w, need_h);
		refresh();
		return (0);
	}

	//RENDER INPUT LINE

	if (!data->flag.start)
	{
		data->flag.start = true;    //// set back to false after chossing was successfull
		data->drop_position = data->columns / 2;
	}

	char message[20];
	if (data->flag.player == AI_MOVE)
		ft_strcpy(message, "AI's turn");
	else
		ft_strcpy(message, "Player's turn");

	message_box(data, cell, message);

	color_input(data, &data->cell);

	render_game(data, &data->cell);
	highlight_landing_cell(data, &data->cell);

	return (0);
}

bool	render_loop(t_data *game)
{
	int ch;

	while (1)
	{
        clear();
		getmaxyx(stdscr, game->terminal_max_y, game->terminal_max_x);
        if (game->terminal_max_x < 43 || game->terminal_max_y < 17)
		{
            printw("Window too small! Minimum size 17 x 43\n");
            int c = getch();
			if (c == ESC)
			{
			   endwin();
			   return false; // ESC gedrückt
			}
			refresh();
            continue;
        }

		if (render_grid(game, &game->cell))
			return false;

		if (game->flag.player == AI_MOVE)
			break ;

		// Get user input
        if (game->flag.player == PLAYER_MOVE)
			ch = getch();

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
		if (ch == ' ' && game->flag.player == PLAYER_MOVE)
		{
			clear();
			refresh();
			if (!check_player_input(game, game->drop_position))
			{
				message_box(game, &game->cell, "You cannot drop the pawn at this column\n");

				continue ;
			}
			//flushinp();
			break ;
		}

		if (ch == KEY_LEFT && game->flag.player == PLAYER_MOVE)
        {
			clear();
			if (game->drop_position - 1 < 0)
			{
				game->drop_position = game->columns - 1;
				//message_box(game, &game->cell, "Move to left not possible\n");
				refresh();
			}
			else
				game->drop_position -= 1;
            continue;
        }
		if (ch == KEY_RIGHT && game->flag.player == PLAYER_MOVE)
        {
			clear();
			if (game->drop_position + 1 == game->columns)
			{
				game->drop_position = game->columns % game->columns;
				//message_box(game, &game->cell, "Move to right not possible\n");
				refresh();
			}
			else
				game->drop_position += 1;
            continue;
        }



	}
	return true;
}



#include "connect4.h"
#include <ncurses.h>



short	get_color(char c)
{

	if (c == PLAYER_COLOR)
	{
		return YELLOW;
	}
	else if (c == AI_COLOR)
	{
		return RED;
	}
    return BLACK;
}

int	color_cell(t_data *data, Cell *cell, int x, int y)
{
	char map_num = data->map[y][x];
	int start_x = 1 + x * (cell->w + 1);
	int start_y = 1 + (y + 1) * (cell->h + 1);

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
			if (color_cell(data, cell, x, y))
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
    int usable_h = data->terminal_max_y - (data->rows + 2);		//same for height

    if (usable_w < data->columns || usable_h < data->rows + 1) // Safety check: if the usable area is smaller than the grid
    {
        cell->w = 2;
        cell->h = 1;
        return;
    }
	cell->w = usable_w / data->columns;					//calc usable cell witdh and height by dividing evenly
	cell->h = usable_h / (data->rows + 1);
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
	int need_h = (data->rows + 1) * (cell->h + 1) + 1;
	if (need_w > data->terminal_max_x || need_h > data->terminal_max_y)
	{
		printw("Terminal too small! Minimum size: [%d, %d]\n", need_w, need_h);
		refresh();
		return (0);
	}

    int y = 0;
    for (int row = 1; row < data->rows + 1; row++)
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

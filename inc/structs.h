

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct cell
{
	int		w;
	int		h;
}	Cell;


typedef struct data
{
	int		rows;
	int		columns;

	int		terminal_max_x;
	int		terminal_max_y;
	char	**map;

	Cell	cell;
}	t_data;



#endif /* STRUCTS_H */
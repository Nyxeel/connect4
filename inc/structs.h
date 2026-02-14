

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct cell
{
	int		w;
	int		h;
}	Cell;

typedef struct flag
{
	bool 	start;
	bool	player;
}	Flag;


typedef struct data
{
	int		rows;
	int		columns;

	int		terminal_max_x;
	int		terminal_max_y;
	char	**map;

	char	start_flag;
	int		drop_position;

	Cell	cell;
	Flag	flag;
}	t_data;



#endif /* STRUCTS_H */
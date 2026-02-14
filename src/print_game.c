

#include "connect4.h"

void	print_game(t_data *data)
{
	for (int i = 0; i < data->rows; i++)
	{
		for(int j = 0; j < data->columns; j++)
		{
			printf("+---");



			if (i == 0)
				print_first_line(data);
			if (j == 0)
				print_first_cell(data);
			else if (j + 1 == data->columns)
				print_last_cells(data);
			else
				print_inbetween_cells(data);

		}



	}
	return ;
}

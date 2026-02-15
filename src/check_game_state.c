
#include "../inc/connect4.h"

/*
0 = nothing
1 = player win
2 = AI win
3 = draw
*/
static int	count_dir(t_data *data, int r, int c, int dr, int dc)
{
	char	token;
	int		count;

	token = data->map[r][c];
	count = 0;
	r += dr;
	c += dc;
	while (r >= 0 && r < data->rows && c >= 0 && c < data->columns
		&& data->map[r][c] == token)
	{
		count++;
		r += dr;
		c += dc;
	}
	return (count);
}

int	check_game_state(t_data *data)
{
	int		directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
	int		empty;
	char	token;
	int		dr;
	int		dc;
	int		total;

	empty = 0;
	for (int r = 0; r < data->rows; r++)
	{
		for (int c = 0; c < data->columns; c++)
		{
			token = data->map[r][c];
			if (token == '0' || token == '.')
			{
				empty = 1;
				continue ;
			}
			if (token != '1' && token != '2')
				continue ;
			for (int i = 0; i < 4; i++)
			{
				dr = directions[i][0];
				dc = directions[i][1];
				total = 1;
				total += count_dir(data, r, c, dr, dc);
				total += count_dir(data, r, c, -dr, -dc);
				if (total >= 4)
					return ((token == '1') ? 1 : 2);
			}
		}
	}
	if (!empty)
		return (3); // draw
	return (0);     // nothing yet
}

bool	check_player_input(t_data *data, int column)
{
	int lines = data->rows - 1;
	char **map = data->map;
	while (lines >= 0)
	{
		if (map[lines][column] == '1' || map[lines][column] == '2' )
			lines--;
		else
		{
			data->map[lines][column] = '2';
			return (true);
		}
	}

	return (false);
}

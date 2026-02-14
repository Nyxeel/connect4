
#include "../inc/connect4.h"
#include "ncurses.h"

void	init_ncurses(void)
{
	initscr(); // Like mlx_init for ncurses basically
	cbreak();
	// Disable line buffering (So you don't need to press enter to get a key input)
	noecho();             // Do not display typed characters
	keypad(stdscr, TRUE); // Enable function keys (like arrow keys)
	curs_set(0);
	// Hide cursor on screen (usually it is blinking in the shell)
	start_color();
	init_pair(YELLOW, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(RED, COLOR_RED, COLOR_RED);
	init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
	init_pair(TEXT_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(TEXT_RED, COLOR_YELLOW, COLOR_BLACK);
	return ;
}

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

static bool	game_loop(t_data *game)
{
	int	state;

	init_ncurses();
	ft_memset(&game->flag, 0, 0);
	while (1)
	{
		if (game->flag.player == AI_MOVE)
		{
			// ft_ai(game);
			if (!render_loop(game))
				return (false);
			sleep(3);
			game->flag.player = PLAYER_MOVE;
			game->flag.start = false;
		}
		else
		{
			// player_input(data);
			if (!render_loop(game))
				return (false);
			game->flag.player = AI_MOVE;
			game->flag.start = false;
			// take_user_input()
		}
		state = check_game_state(game);
		if (state == 0)
			continue ;
		else if (state == 1)
			message_box(game, &game->cell, "Player wins");
		else if (state == 2)
			message_box(game, &game->cell, "AI wins");
		else if (state == 3)
			message_box(game, &game->cell, "Draw");
		if (state != 0)
			break ;
		// ft_think();
	}
	endwin();
	return (true);
}

bool	start_game(t_data *data)
{
	int	start_flag;

	start_flag = 0;
	if (((start_flag = rand() % 2) == AI))
	{
		ft_printf("AI START\n");
		data->flag.player = AI_MOVE;
		game_loop(data);
	}
	else
	{
		ft_printf("PLAYER START\n");
		data->flag.player = PLAYER_MOVE;
		game_loop(data);
	}
	return (true);
}


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


static bool	game_loop(t_data *game)
{
	int	state;

	init_ncurses();
	ft_memset(&game->flag, 0, 0);
/* 	game->map[0][0] = '1';
	game->map[game->rows - 5][0] = '1';

	game->map[game->rows - 4][0] = '1';
	game->map[game->rows - 3][0] = '1';
	game->map[game->rows - 2][0] = '1';
	game->map[game->rows - 1][0] = '1'; */

	while (1)
	{
		refresh();

		if (game->flag.player == AI_MOVE)
		{
			ai_make_move(game);
			if (!render_loop(game))
				return (false);
			sleep(2);
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
			refresh();

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
	if (((start_flag = rand() % 2) == AI_MOVE))
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

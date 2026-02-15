
#include "../inc/connect4.h"
#include "ncurses.h"

void	init_ncurses(t_data *game)
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
	init_pair(TEXT_RED, COLOR_RED, COLOR_BLACK);
	init_pair(TEXT_BLUE, COLOR_BLUE, COLOR_BLACK);


	compute_cell_size(game, &game->cell);

	return ;
}


static bool	bonus_game_loop(t_data *game)
{
	int	state;

	init_ncurses(game);
	ft_memset(&game->flag, 0, 0);

	while (1)
	{


		if (game->flag.player == AI_MOVE)
		{
			ai_make_move(game);
			if (!render_loop(game))
				return (false);
			// sleep(3);
			game->flag.player = PLAYER_MOVE;
			game->flag.start = false;
			refresh();
		}
		else
		{
			if (!render_loop(game))
				return (false);
			game->flag.player = AI_MOVE;
			game->flag.start = false;
			refresh();
		}
		state = check_game_state(game);
		if (state == 0)
			continue ;
		else
			clear();
		game->flag.player = COLOR_BLUE;
		if (state == 1)
			message_box(game, &game->cell, "AI wins");
		else if (state == 2)
			message_box(game, &game->cell, "Player wins");
		else if (state == 3)
			message_box(game, &game->cell, "Draw");
		if (state != 0)
			break ;

	}
	sleep(3);
	endwin();
	return (true);
}

bool	start_game(t_data *data)
{
	int	start_flag;

	start_flag = 0;
	if (((start_flag = rand() % 2) == AI_MOVE))
		data->flag.player = AI_MOVE;
	else
		data->flag.player = PLAYER_MOVE;


	if (data->flag.bonus)
		bonus_game_loop(data);
	else
		printf("To start game add 'bonus' as argv[3]\n");
	return (true);
}

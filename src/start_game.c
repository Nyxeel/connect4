
#include "../inc/connect4.h"

#include "ncurses.h"


void	init_ncurses()
{

	initscr();              // Like mlx_init for ncurses basically
    cbreak();               // Disable line buffering (So you don't need to press enter to get a key input)
    noecho();               // Do not display typed characters
    keypad(stdscr, TRUE);   // Enable function keys (like arrow keys)
    curs_set(0);            // Hide cursor on screen (usually it is blinking in the shell)

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

	init_ncurses();
	ft_memset(&game->flag, 0, 0);

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

		/* if (game->start_flag == AI)
			//AI_CALC_FIRST_MOVE
			game->start_flag = 0;
		else
			//AI_CALC_FIRST_MOVE
			game->start_flag = 1; */
		//update_game_map
		//print_game_map
		//check_map() FOR WINNING CONDITION

		// Get user input
        int ch = getch();

		if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, game->terminal_max_y, game->terminal_max_x);
            continue;
        }
		if (ch == KEY_LEFT)
        {

			if (game->drop_position - 1 < 0)
			{
				clear();
				printw("Move to left not possible\n");
			}
			else
				game->drop_position -= 1;
            continue;
        }
		if (ch == KEY_RIGHT)
        {
			clear();
			if (game->drop_position + 1 >= game->columns)
			{
				clear();
				printw("Move to right not possible\n");
			}
			else
				game->drop_position += 1;
            continue;
        }


		if (game->flag.player == AI_MOVE)
		{
			//ft_ai(game);
			//render_game(data, &game->cell);
			game->flag.player = PLAYER_MOVE;

		}
		else
		{
			//player_input(data);
			//render_game(data, &game->cell);
			game->flag.player = AI_MOVE;

			//take_user_input()


		}


		//sleep(2);


		//ft_think();

	}
	return (true);
}

bool	start_game(t_data *data)
{
	int start_flag = 0;

	if (((start_flag = rand() % 2) == AI))
	{
		printf("AI START\n" );
		data->flag.player = AI_MOVE;
		game_loop(data);
	}
	else
	{
		printf("PLAYER START\n");
		data->flag.player = PLAYER_MOVE;
		game_loop(data);
	}
	return true ;
}

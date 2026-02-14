
#include "connect4.h"
#include <ncurses.h>




static bool	game_loop(t_data *game, int start_flag)
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


	game->map[0][0] = '1'; //AI COLOR RED
	game->map[1][0] = '2'; //PLAYER COLOR YELLOW


/* 	if (start_flag == PLAYER_START)
		print_map(game); */

	//print_grid(data);
	while (1)
	{

		getmaxyx(stdscr, game->terminal_max_y, game->terminal_max_x);
        if (game->terminal_max_x < 43 || game->terminal_max_y < 17) {
            clear();
            printw("Window too small! Minimum\n");
            getch();
            continue;
        }

		if (render_grid(game, &game->cell))
			return false;

		if (start_flag == AI)
			//AI_CALC_FIRST_MOVE
			start_flag = 0;
		else
			//AI_CALC_FIRST_MOVE
			start_flag = 1;
		//update_game_map
		//print_game_map
		//check_map() FOR WINNING CONDITION

		// Get user input
        int ch = getch();

		if (ch == KEY_RESIZE) {
            getmaxyx(stdscr, game->terminal_max_y, game->terminal_max_x);
            continue;
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
		game_loop(data, AI);
	}
	else
	{
		printf("PLAYER START\n");
		game_loop(data, PLAYER);
	}
	return true ;
}

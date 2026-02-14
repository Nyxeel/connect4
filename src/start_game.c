
#include "connect4.h"



static bool	game_loop(t_data *game, int start_flag)
{
	(void) game;

	sleep(2);

	if (VERBOSE)
		printf("INSIDE GAMELOOP\n");

	if (start_flag == PLAYER_START)
		print_map(game);

	//print_grid(data);
	while (1)
	{

		if (start_flag == AI_START)
			//AI_CALC_FIRST_MOVE
			start_flag = 0;
		else
			//AI_CALC_FIRST_MOVE
			start_flag = 1;
		//update_game_map
		//print_game_map
		//check_map() FOR WINNING CONDITION


		sleep(2);
		break;
	}
	return (true);
}

bool	start_game(t_data *data)
{
	int start_flag = 0;

	if (((start_flag = rand() % 2) == AI_START))
	{
		printf("AI START\n" );
		game_loop(data, AI_START);
	}
	else
	{
		printf("PLAYER START\n");
		game_loop(data, PLAYER_START);
	}
	return true ;
}

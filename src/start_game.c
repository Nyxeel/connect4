
#include "../inc/connect4.h"


bool	start_game(t_data *data)
{
	int	start_flag;

	start_flag = 0;
	if (((start_flag = rand() % 2) == AI_MOVE))
		data->flag.player = AI_MOVE;
	else
		data->flag.player = PLAYER_MOVE;

	bool exit;
	if (data->flag.bonus == true)
		exit = bonus_game_loop(data);
	else
		exit = game_loop(data);
	if (exit == false)
		return (false);
	return (true);
}

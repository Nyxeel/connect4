/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:10:27 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/15 15:45:39 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/connect4.h"


bool	game_loop(t_data *game)
{
	//int	state;
	if (game->rows >= 20 || game->columns >= 40)
		return (print_error("Your computer cannot handle such a big grid size!\nPlease contact Bocal for better hardware\n"), false);

	game->map[8][6] = '1';
	game->map[8][7] = '2';
	int i = 0;
	while (i < 2)
	{
		if (game->flag.player == AI_MOVE)
		{
			print_grid(game, "\033[31mAI's turn\033[0m");

			ft_sleep(2);
			//ai_make_move(game);
			game->flag.player = PLAYER_MOVE;
			game->flag.start = false;
		}
		else
		{
			print_grid(game, "\033[33mPlayer's turn\033[0m");
			game->flag.player = AI_MOVE;
			game->flag.start = false;
		}
		i++;

	/* 	state = check_game_state(game);
		if (state == 0)
			continue ; */

	/* 	//PRINT IN BLUE//game->flag.player = COLOR_BLUE;
		if (state == 1)
			message_box(game, &game->cell, "AI wins");
		else if (state == 2)
			message_box(game, &game->cell, "Player wins");
		else if (state == 3)
			message_box(game, &game->cell, "Draw");
		if (state != 0)
			break ; */

	}
	//render_game(game, &game->cell);
	ft_sleep(5);

	return (true);
}

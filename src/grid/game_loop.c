/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:10:27 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/15 17:13:19 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/connect4.h"


bool	game_loop(t_data *game)
{
	//int	state;
	if (game->rows >= 20 || game->columns >= 40)
		return (print_error("Your computer cannot handle such a big grid size!\nPlease contact Bocal for better hardware\n"), false);


	ft_printf("\033[33mGAME START\033[0m\n");
	game->flag.start = true;

	while (1)
	{
		if (game->flag.player == AI_MOVE)
		{
				if (game->flag.start)
			{

				ft_printf("\n");
				print_grid(game);
				game->flag.start = false;
			}
			ft_printf("\033[31mAI is thinking\033[0m");
			ft_sleep(1);
			ft_printf("\033[31m .\033[0m");
			ft_sleep(1);
			ft_printf("\033[31m .\033[0m");
			ft_sleep(1);
			ft_printf("\033[31m .\033[0m");
			int col = ai_make_move(game);
			print_grid(game);
			ft_printf("\033[31mAI dropped pawn at column %i\033[0m\n\n", col + 1);
			//ft_sleep(1);
			game->flag.player = PLAYER_MOVE;
			game->flag.start = false;
		}
		else
		{
			if (game->flag.start)
			{

				ft_printf("DEBUGGGGGG\n");
				print_grid(game);
				game->flag.start = false;
			}
			ft_printf( "\033[33mPlayer's turn\033[0m\n");
			take_player_input(game);
			print_grid(game);
			game->flag.player = AI_MOVE;
			game->flag.start = false;
		}


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


	return (true);
}

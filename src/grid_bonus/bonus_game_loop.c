/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_game_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 13:56:02 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/15 14:34:31 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/connect4.h"
#include "ncurses.h"

static void	init_ncurses(t_data *game)
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

bool	bonus_game_loop(t_data *game)
{
	int	state;

	init_ncurses(game);
	while (1)
	{
		if (game->flag.player == AI_MOVE)
		{
			if (!render_loop(game))
				return (false);

			ft_sleep(2);
			int target_col = ai_make_move(game);
			render_move(game, target_col);
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
	render_game(game, &game->cell);
	ft_sleep(5);
	endwin();
	return (true);
}

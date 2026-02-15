/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ai_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:46:17 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/15 04:26:09 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connect4.h"
#include "ncurses.h"


void	render_move(t_data *data, int best_col)
{
	int x = data->drop_position;
	int y = best_col;

	int moves;
	if (x > y)
		moves = x - y;
	else
		moves = y - x;

	while (moves > 0)
	{
		if (x > y)
			data->drop_position--;
		else if (x == y)
			continue;
		else
			data->drop_position++;
		color_input(data, &data->cell);
		refresh();
		usleep(500000); // 500ms delay for animation

		moves--;
	}
	usleep(500000); // 500ms delay for animation
	refresh();
	return ;
}
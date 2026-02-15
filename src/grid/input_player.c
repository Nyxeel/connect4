/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 16:09:03 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/15 18:58:42 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/connect4.h"

int	parse_input(t_data *data, char *str)
{
	if (*str == '\n')
		return (0);
	char *trim = ft_strtrim(str, "\n");
	if (!digit_check(trim))
	{
		print_error("Only numbers are valid!");
		return (0);
	}
	if (int_overflow_check(trim))
	{
		print_error("Number would overflowed");
		return (0);
	}
	int nb = ft_atoi(trim);
	if (nb > data->columns || nb < 1)
	{
		print_error("Number out of grid scope\n");
		return (0);
	}
	int lines = data->rows - 1;
	int column = nb - 1;
	char **map = data->map;
	while (lines >= 0)
	{
		if (map[lines][column] == '1' || map[lines][column] == '2' )
			lines--;
		else
		{
			data->map[lines][column] = '2';
			return (1);
		}
	}
	print_error("You cannot drop the pawn at this column\n");
	return (0);
}

int	take_player_input(t_data *data)
{
	char *line;

	ft_printf("Choose the column number to drop the pawn: ");
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			return (ERROR);
		if (line)
		{
			if (!parse_input(data, line))
			{
				free(line);
				ft_printf("Try again: ");
				continue ;
			}
			break ;
		}
	}
	free(line);
	return (SUCCESS);
}




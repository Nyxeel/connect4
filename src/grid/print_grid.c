/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 14:08:51 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/15 16:57:55 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/connect4.h"

void	print_numbers(t_data *data)
{
	for (int i = 1; i <= data->columns ; i++)
	{
		if (i <= 10)
			ft_printf("\033[34m  %i ", i);
		else
			ft_printf("\033[34m %i ", i);
	}
	ft_printf("\033[0m\n");
	return ;
}


void	print_colors(t_data *data, int x, int y)
{
	//printf("X:%i\nY:%i", x, y);
	if (data->map[x][y] == '1')
		ft_printf("\033[41m \033[0m");
	else if (data->map[x][y] == '2')
		ft_printf("\033[43m \033[0m");
	else
		ft_printf(" ");
	return ;
}


void	print_grid(t_data *data)
{

	/// RENDER GAME MAP


	ft_printf("\n\n");
	print_numbers(data);

	int line = 0;
	int column;

    for (int row = 0; row < data->rows; row++)
    {
        for (int col = 0; col < data->columns; col++)
        {
            ft_printf("+");
            for (int i = 0; i < 3; i++)
                ft_printf("─");
        }
        ft_printf("+\n");
		column = -1;
        for (int h = 0; h < 1; h++)
        {
            for (int col = 0; col < data->columns; col++)
            {
				++column;
                ft_printf("│");
                for (int i = 0; i < 3; i++)
                	print_colors(data, line, column);
            }
			line++;
            ft_printf("│");
        }
		ft_printf("\n");
    }
    for (int col = 0; col < data->columns; col++)
    {
        ft_printf("+");
        for (int i = 0; i < 3; i++)
            ft_printf("─");

    }
    ft_printf("+\n\n");

}

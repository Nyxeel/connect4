/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 20:36:14 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/15 20:40:24 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct cell {
  int w;
  int h;
} Cell;

typedef struct flag {
  bool start;
  int player;
  bool color;
  bool bonus;
  bool no_render;
} Flag;

typedef struct data {
  int rows;
  int columns;

  int terminal_max_x;
  int terminal_max_y;
  char **map;

  char start_flag;
  int drop_position;

  Cell cell;
  Flag flag;
} t_data;

#endif /* STRUCTS_H */
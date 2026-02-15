/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjelinek <pjelinek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 18:59:31 by pjelinek          #+#    #+#             */
/*   Updated: 2026/02/15 21:07:00 by pjelinek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
#define GAME_H

#include "structs.h"

/* ************************************************************************** */
/*                                GAME FLOW                                   */
/* ************************************************************************** */

bool init_game(t_data *data);
bool start_game(t_data *data);
bool game_loop(t_data *game);
bool bonus_game_loop(t_data *game);
bool render_loop(t_data *game);
int check_game_state(t_data *data);

/* ************************************************************************** */
/*                                RENDERING                                   */
/* ************************************************************************** */

int render_game(t_data *data, Cell *cell);
int render_grid(t_data *data, Cell *cell);
void render_move(t_data *data, int target_row);
void print_map(t_data *data);
void print_grid(t_data *data);
void message_box(t_data *data, Cell *cell, char *str);
void reset_message_box(t_data *data, Cell *cell);
void compute_cell_size(t_data *data, Cell *cell);
short get_color(char c);

/* ************************************************************************** */
/*                                PLAYER INPUT                                */
/* ************************************************************************** */

int take_player_input(t_data *data);
bool check_player_input(t_data *data, int column);
bool digit_check(const char *str);
void color_input(t_data *data, Cell *cell);

/* ************************************************************************** */
/*                                   AI                                       */
/* ************************************************************************** */

int ai_make_move(t_data *data);

/* ************************************************************************** */
/*                        INITIALIZATION & PARSING                            */
/* ************************************************************************** */

bool parse(t_data *data, char **argv);
void init_signals(void);

/* ************************************************************************** */
/*                                UTILITIES                                   */
/* ************************************************************************** */

void print_error(char *str);
void free_split(char **split);
void ft_sleep(int sek);
void ft_think(void);

#endif /* GAME_H */

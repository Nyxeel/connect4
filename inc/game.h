
#ifndef GAME_H
#define GAME_H

void print_map(t_data *data);
void print_error(char *str);
bool parse(t_data *data, char **argv);
bool init_game(t_data *data);
bool start_game(t_data *data);

void init_signals(void);
void ft_think();

int render_grid(t_data *data, Cell *cell);
void color_input(t_data *data, Cell *cell);
short get_color(char c);

void message_box(t_data *data, Cell *cell, char *str);

bool render_loop(t_data *game);
int check_game_state(t_data *data);

bool check_player_input(t_data *data, int column);
int render_game(t_data *data, Cell *cell);


int 	ai_make_move(t_data *data);
void compute_cell_size(t_data *data, Cell *cell);
void	reset_message_box(t_data *data, Cell *cell);
void	render_move(t_data *data, int target_row);

bool	game_loop(t_data *game);
void	print_grid(t_data *data, char *str);


bool	bonus_game_loop(t_data *game);


void free_split(char **split);
void	ft_sleep(int sek);


#endif /* GAME_H */

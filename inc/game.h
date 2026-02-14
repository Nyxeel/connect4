
#ifndef GAME_H
# define GAME_H

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

void	update_message_box(t_data *data, Cell *cell, char *str);;

void free_split(char **split);

#endif /* GAME_H */
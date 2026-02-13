#ifndef GAME_H
# define GAME_H



void	print_map(t_data *data);
void	print_error(char *str);
bool	parse(t_data *data, char **argv);
bool	init_game(t_data *data);
bool	start_game(t_data *data);

void	init_signals(void);




void	free_split(char **split);


#endif /* GAME_H */
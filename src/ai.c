#include "../inc/connect4.h"
#include <limits.h>

// Counts sequences of 4 to score the board state
static int	evaluate_window(int count_ai, int count_player, int count_empty)
{
	int	score;

	score = 0;
	if (count_ai == 4)
		score += 10000;
	else if (count_ai == 3 && count_empty == 1)
		score += 100;
	else if (count_ai == 2 && count_empty == 2)
		score += 10;
	if (count_player == 3 && count_empty == 1)
		score -= 80; // Block player
	return (score);
}

static int	checks(t_data *data, int score)
{
	int		r;
	int		c;
	int		count_ai;
	int		count_player;
	int		count_empty;
	char	**map;

	r = -1;
	map = data->map;
	while (++r < data->rows)
	{
		c = -1;
		while (++c <= data->columns - 4)
		{
			count_ai = (map[r][c] == '1') + (map[r][c + 1] == '1') + (map[r][c
					+ 2] == '1') + (map[r][c + 3] == '1');
			count_player = (map[r][c] == '2') + (map[r][c + 1] == '2')
				+ (map[r][c + 2] == '2') + (map[r][c + 3] == '2');
			count_empty = 4 - count_ai - count_player;
			score += evaluate_window(count_ai, count_player, count_empty);
		}
	}
	r = -1;
	while (++r <= data->rows - 4)
	{
		c = -1;
		while (++c < data->columns)
		{
			count_ai = (map[r][c] == '1') + (map[r + 1][c] == '1') + (map[r
					+ 2][c] == '1') + (map[r + 3][c] == '1');
			count_player = (map[r][c] == '2') + (map[r + 1][c] == '2') + (map[r
					+ 2][c] == '2') + (map[r + 3][c] == '2');
			count_empty = 4 - count_ai - count_player;
			score += evaluate_window(count_ai, count_player, count_empty);
		}
	}
	r = -1;
	while (++r <= data->rows - 4)
	{
		c = -1;
		while (++c <= data->columns - 4)
		{
			count_ai = (map[r][c] == '1') + (map[r + 1][c + 1] == '1') + (map[r
					+ 2][c + 2] == '1') + (map[r + 3][c + 3] == '1');
			count_player = (map[r][c] == '2') + (map[r + 1][c + 1] == '2')
				+ (map[r + 2][c + 2] == '2') + (map[r + 3][c + 3] == '2');
			count_empty = 4 - count_ai - count_player;
			score += evaluate_window(count_ai, count_player, count_empty);
		}
	}
	r = 2;
	while (++r < data->rows)
	{
		c = -1;
		while (++c <= data->columns - 4)
		{
			count_ai = (map[r][c] == '1') + (map[r - 1][c + 1] == '1') + (map[r
					- 2][c + 2] == '1') + (map[r - 3][c + 3] == '1');
			count_player = (map[r][c] == '2') + (map[r - 1][c + 1] == '2')
				+ (map[r - 2][c + 2] == '2') + (map[r - 3][c + 3] == '2');
			count_empty = 4 - count_ai - count_player;
			score += evaluate_window(count_ai, count_player, count_empty);
		}
	}
	return (score);
}

// find the first empty row in a column
static int	get_available_row(t_data *data, int col)
{
	for (int r = data->rows - 1; r >= 0; r--)
	{
		if (data->map[r][col] == '.') // Assuming '.' is empty
			return (r);
	}
	return (-1);
}

static int	score_position(t_data *data)
{
	int		score;
	int		center_col;
	char	**map;
	int		r;

	score = 0;
	map = data->map;
	// Focus on center column preference (strategic advantage)
	center_col = data->columns / 2;
	for (r = 0; r < data->rows; r++)
	{
		if (map[r][center_col] == '1')
			score += 3;
	}
	score = checks(data, score);
	return (score);
}

static void	get_column_order(int *order, int columns)
{
	int	center;
	int	i;

	center = columns / 2;
	i = 0;
	order[i++] = center;
	for (int delta = 1; delta <= center; delta++)
	{
		if (center - delta >= 0)
			order[i++] = center - delta;
		if (center + delta < columns)
			order[i++] = center + delta;
	}
}

static int	is_winning_move(t_data *data, int r, int c, char symbol)
{
	int	directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
	int	count;
	int	dr;
	int	dc;
	int	nr;
	int	nc;

	// Order: Horizontal, Vertical, Diagonal, Anti-Diagonal
	for (int i = 0; i < 4; i++)
	{
		count = 1;
		// Check both directions (positive and negative)
		for (int dir = -1; dir <= 1; dir += 2)
		{
			dr = directions[i][0] * dir;
			dc = directions[i][1] * dir;
			nr = r + dr;
			nc = c + dc;
			while (nr >= 0 && nr < data->rows && nc >= 0 && nc < data->columns
				&& data->map[nr][nc] == symbol)
			{
				count++;
				nr += dr;
				nc += dc;
			}
		}
		if (count >= 4)
			return (1);
	}
	return (0);
}

static int	minimax(t_data *data, int depth, int alpha, int beta,
		int is_maximizing, int last_r, int last_c)
{
	int	r;
	int	eval;
	int	col_order[data->columns];
	int	max_eval;
	int	c;
	int	min_eval;

	// Check if the previous move won the game
	if (last_r != -1)
	{
		if (is_maximizing == 0 && is_winning_move(data, last_r, last_c, '1'))
			return (1000000 + depth); // AI won
		if (is_maximizing == 1 && is_winning_move(data, last_r, last_c, '2'))
			return (-1000000 - depth); // Player won
	}
	if (depth == 0)
		return (score_position(data));
	// 1. Base Case: Leaf node or Terminal state
	if (depth == 0)
		return (score_position(data));
	get_column_order(col_order, data->columns);
	if (is_maximizing)
	{
		max_eval = INT_MIN;
		for (int i = 0; i < data->columns; i++)
		{
			c = col_order[i];
			r = get_available_row(data, c);
			if (r != -1)
			{
				data->map[r][c] = '1'; // AI Move
				eval = minimax(data, depth - 1, alpha, beta, 0, r, c);
				data->map[r][c] = '.';
				if (eval > max_eval)
					max_eval = eval;
				if (eval > alpha)
					alpha = eval;
				if (beta <= alpha)
					break ; // Pruning
			}
		}
		return (max_eval);
	}
	else // Minimizing Player (User)
	{
		min_eval = INT_MAX;
		for (int i = 0; i < data->columns; i++)
		{
			c = col_order[i];
			r = get_available_row(data, c);
			if (r != -1)
			{
				data->map[r][c] = '2'; // Player Move
				eval = minimax(data, depth - 1, alpha, beta, 1, r, c);
				data->map[r][c] = '.';
				if (eval < min_eval)
					min_eval = eval;
				if (eval < beta)
					beta = eval;
				if (beta <= alpha)
					break ; // Pruning
			}
		}
		return (min_eval);
	}
}

void	ai_make_move(t_data *data)
{
	int	best_score;
	int	best_col;
	int	target_row;
	int	r;
	int	score;

	best_score = 0;
	best_col = 0;
	target_row = 0;
	for (int c = 0; c < data->columns; c++)
	{
		r = get_available_row(data, c);
		if (r != -1)
		{
			data->map[r][c] = '1';
			// TODO: Dynamic Depth based on Grid size
			score = minimax(data, 4, INT_MIN, INT_MAX, 0, r, c);
			data->map[r][c] = '.';
			if (score > best_score)
			{
				best_score = score;
				best_col = c;
				target_row = r;
			}
		}
	}
	data->map[target_row][best_col] = '1';
}

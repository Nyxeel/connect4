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

// Helper to find the first empty row in a column
static int	get_available_row(t_data *data, int col)
{
	for (int r = data->rows - 1; r >= 0; r--)
	{
		if (data->map[r][col] == '.') // Assuming '.' is empty
			return (r);
	}
	return (-1);
}

// Simple heuristic: scans board and scores positions
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

static int	minimax(t_data *data, int depth, int alpha, int beta)
{
	int	max_eval;
	int	r;
	int	eval;

	if (depth == 0)
		return (score_position(data));
	max_eval = INT_MIN;
	for (int c = 0; c < data->columns; c++)
	{
		r = get_available_row(data, c);
		if (r != -1)
		{
			data->map[r][c] = '1';
			eval = minimax(data, depth - 1, alpha, beta);
			data->map[r][c] = '.'; // Undo move
			if (eval > max_eval)
				max_eval = eval;
			if (eval > alpha)
				alpha = eval;
			if (beta <= alpha)
				break ;
		}
	}
	return (max_eval);
}

void	ai_make_move(t_data *data)
{
	int	best_score;
	int	best_col;
	int	target_row;
	int	r;
	int	score;

	best_score = INT_MIN;
	best_col = 0;
	target_row = 0;
	for (int c = 0; c < data->columns; c++)
	{
		r = get_available_row(data, c);
		if (r != -1)
		{
			data->map[r][c] = '1';
			// TODO: Dynamic Depth based on Grid size
			score = minimax(data, 4, INT_MIN, INT_MAX);
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

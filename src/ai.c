#include "../inc/connect4.h"
#include <limits.h>

/* // Counts sequences of 4 to score the board state
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
} */

static int	checks(t_data *data, int score)
{

	char	v;
	int		max_r;
	int		max_c;
	int		dr;
	int		dc;
	int		r_start_min;
	int		r_start_max;
	int		c_start_min;
	int		c_start_max;
	int		count_ai;
	int		count_player;
	int		count_empty;
	char	**map = data->map;


	// Directions: horizontal, vertical, diag, anti-diag
	int dirs[4][2] = {
		{0, 1}, // to the right
		{1, 0}, // downwards
		{1, 1}, // to the right and downwards
		{1, -1} // to the left and downwards
	};
	max_r = data->rows;
	max_c = data->columns;
	for (int d = 0; d < 4; d++)
	{
		dr = dirs[d][0];
		dc = dirs[d][1];
		// Compute valid start ranges for this direction
		r_start_min = 0;
		if (dr != 0)
			r_start_max = max_r - 4;
		else
			r_start_max = max_r - 1;
		if (dc < 0)
			c_start_min = 3;
		else
			c_start_min = 0;
		if (dc > 0)
			c_start_max = max_c - 4;
		else
			c_start_max = max_c - 1;
		for (int r = r_start_min; r <= r_start_max; r++)
		{
			for (int c = c_start_min; c <= c_start_max; c++)
			{
				count_ai = 0;
				count_player = 0;
				// Examine the 4 cells of this window
				for (int k = 0; k < 4; k++)
				{
					v = map[r + dr * k][c + dc * k];
					if (v == '1')
						count_ai++;
					else if (v == '2')
						count_player++;
				}
				// Mixed windows cannot produce scoring patterns
				if (count_ai && count_player)
					continue ;
				count_empty = 4 - count_ai - count_player;
				// Inline scoring logic
				if (count_ai == 4)
					score += 10000;
				else if (count_ai == 3 && count_empty == 1)
					score += 100;
				else if (count_ai == 2 && count_empty == 2)
					score += 10;
				if (count_player == 3 && count_empty == 1)
					score -= 80;
			}
		}
	}
	return (score);
}

// find the first empty row in a column
static int	get_available_row(t_data *data, int col)
{



	for (int r = data->rows - 1; r >= 0; r--)
	{
		if (data->map[r][col] == '0') // Assuming '0' is empty
			return (r);
	}
	return (-1);
}

static int	score_position(t_data *data)
{
	char **map = data->map;
	int		center_col;
	int		score;

	int		r;

	score = 0;

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

	int		directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
	int		count;
	int		dr;
	int		dc;
	int		nr;
	int		nc;


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

	int		r;
	int		eval;
	int		col_order[data->columns];
	int		max_eval;
	int		c;
	int		min_eval;


	// Check if the previous move won the game
	if (last_r != -1)
	{
		if (is_maximizing == 0 && is_winning_move(data, last_r, last_c, '1'))
			return (1000000 + depth); // AI won
		if (is_maximizing == 1 && is_winning_move(data, last_r, last_c, '2'))
			return (-1000000 - depth); // Player won
	}
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
				data->map[r][c] = '0';
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
				data->map[r][c] = '0';
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

/* static int	get_dynamic_depth(t_data *data)
{

	float	fill_ratio;
	int		total_cells;
	int		playable_cols;
	int		pieces_placed;
	int		depth;


	total_cells = data->rows * data->columns;
	playable_cols = 0;
	pieces_placed = 0;
	// Find playable columns and approximate pieces placed
	for (int c = 0; c < data->columns; c++)
	{
		if (data->map[0][c] == '.')
			playable_cols++;
		// Find how many pieces are in each column to get total count
		for (int r = 0; r < data->rows; r++)
		{
			if (data->map[r][c] != '.')
			{
				pieces_placed += (data->rows - r);
				break ;
			}
		}
	}
	// Base Depth based on grid size and vibes
	if (total_cells <= 42)
		depth = 7;
	else if (total_cells <= 72)
		depth = 6;
	else
		depth = 4;
	// Dynamic Scaling
	if (playable_cols <= data->columns / 2)
		depth += 2;
	else if (playable_cols <= data->columns / 1.5)
		depth += 1;
	// fill-ratio = less pieces -> more depth ! less paths
	fill_ratio = (float)pieces_placed / (float)total_cells;
	if (fill_ratio > 0.75f)
		depth += 3;
	else if (fill_ratio > 0.50f)
		depth += 1;
	// Hard Caps cause ynails
	if (depth > 12)
		depth = 12;
	if (depth < 4)
		depth = 4;
	return (depth);
} */

int	ai_make_move(t_data *data)
{

	int		best_score;
	int		best_col;
	int		target_row;
	int		r;
	int		score;


	best_score = 0;
	best_col = 0;
	target_row = 0;
	//int dyn_depth = get_dynamic_depth(data);
	for (int c = 0; c < data->columns; c++)
	{
		// perror("ACCESS\n");

		r = get_available_row(data, c);
		if (r != -1)
		{
			data->map[r][c] = '1';
			// TODO: Dynamic Depth based on Grid size
			score = minimax(data, 4, INT_MIN, INT_MAX, 0, r, c);
			data->map[r][c] = '0';
			if (score > best_score)
			{
				best_score = score;
				best_col = c;
				target_row = r;
			}
			data->map[r][c] = '0';
		}
	}
	// perror("NO ACCESS\n");


	data->map[target_row][best_col] = '1';
	return (best_col);
}

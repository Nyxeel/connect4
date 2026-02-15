#include "../inc/connect4.h"
#include <limits.h>
#include <ncurses.h>

// Actual game + 2 columns to left and right
typedef struct s_bounds
{
	int min_r, max_r;
	int min_c, max_c;
}			t_bounds;

static void	get_board_bounds(t_data *data, t_bounds *bounds)
{
	int	found;

	bounds->min_r = data->rows;
	bounds->max_r = -1;
	bounds->min_c = data->columns;
	bounds->max_c = -1;
	found = 0;
	for (int c = 0; c < data->columns; c++)
	{
		// Check if column is empty
		if (data->map[data->rows - 1][c] != '.')
		{
			if (c < bounds->min_c)
				bounds->min_c = c;
			if (c > bounds->max_c)
				bounds->max_c = c;
			found = 1;
		}
	}
	if (!found)
	{ // Empty board
		bounds->min_c = data->columns / 2;
		bounds->max_c = data->columns / 2;
		bounds->min_r = data->rows / 2;
		bounds->max_r = data->rows / 2;
		return ;
	}
	// Expand bounds slightly to check threats formed by empty spaces
	bounds->min_c = (bounds->min_c - 2 < 0) ? 0 : bounds->min_c - 2;
	bounds->max_c = (bounds->max_c + 2 >= data->columns) ? data->columns
		- 1 : bounds->max_c + 2;
	bounds->max_r = data->rows - 1;
	bounds->min_r = 0;
}

static int	evaluate_window(int ai, int player, int empty)
{
	int	score;

	score = 0;
	if (ai == 4)
		return (1000000);
	if (player == 4)
		return (-1000000);
	if (ai == 3 && empty == 1)
		score += 100;
	if (ai == 2 && empty == 2)
		score += 10;
	if (player == 3 && empty == 1)
		score -= 800; // Block player from winning
	if (player == 2 && empty == 2)
		score -= 15;
	return (score);
}

static int	score_position(t_data *data)
{
	int			score;
	char		**map;
	int			rows;
	int			cols;
	t_bounds	b;
	int			center;
	int			em;
	char		cell;
	int			ai;
	int			pl;

	ai = 0, pl = 0;
	score = 0;
	map = data->map;
	rows = data->rows;
	cols = data->columns;
	// Get played area to avoid scanning 200 empty columns ermium
	get_board_bounds(data, &b);
	// Center Column Preference, cause apparently good
	center = cols / 2;
	for (int r = 0; r < rows; r++)
		if (map[r][center] == '1')
			score += 10;
	// Horizontal (-)
	for (int r = 0; r < rows; r++)
	{
		for (int c = b.min_c; c <= b.max_c - 3; c++)
		{
			ai = 0, pl = 0, em = 0;
			for (int k = 0; k < 4; k++)
			{
				cell = map[r][c + k];
				if (cell == '1')
					ai++;
				else if (cell == '2')
					pl++;
				else
					em++;
			}
			score += evaluate_window(ai, pl, em);
		}
	}
	// Vertical (|)
	for (int c = b.min_c; c <= b.max_c; c++)
	{
		for (int r = 0; r <= rows - 4; r++)
		{
			ai = 0, pl = 0, em = 0;
			for (int k = 0; k < 4; k++)
			{
				cell = map[r + k][c];
				if (cell == '1')
					ai++;
				else if (cell == '2')
					pl++;
				else
					em++;
			}
			score += evaluate_window(ai, pl, em);
		}
	}
	// Diagonal (\)
	for (int r = 0; r <= rows - 4; r++)
	{
		for (int c = b.min_c; c <= b.max_c - 3; c++)
		{
			ai = 0, pl = 0, em = 0;
			for (int k = 0; k < 4; k++)
			{
				cell = map[r + k][c + k];
				if (cell == '1')
					ai++;
				else if (cell == '2')
					pl++;
				else
					em++;
			}
			score += evaluate_window(ai, pl, em);
		}
	}
	// Diagonal (/)
	for (int r = 3; r < rows; r++)
	{
		for (int c = b.min_c; c <= b.max_c - 3; c++)
		{
			ai = 0, pl = 0, em = 0;
			for (int k = 0; k < 4; k++)
			{
				cell = map[r - k][c + k];
				if (cell == '1')
					ai++;
				else if (cell == '2')
					pl++;
				else
					em++;
			}
			score += evaluate_window(ai, pl, em);
		}
	}
	return (score);
}

static int	get_available_row(t_data *data, int col)
{
	for (int r = data->rows - 1; r >= 0; r--)
		if (data->map[r][col] == '.')
			return (r);
	return (-1);
}

static int	is_winning_move(t_data *data, int r, int c, char symbol)
{
	int	directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
	int	nr;
	int	nc;

	// Simplified check
	for (int d = 0; d < 4; d++)
	{
		int count = 1; // Count just placed piece
		// Check forward
		for (int k = 1; k < 4; k++)
		{
			nr = r + directions[d][0] * k;
			nc = c + directions[d][1] * k;
			if (nr < 0 || nr >= data->rows || nc < 0 || nc >= data->columns
				|| data->map[nr][nc] != symbol)
				break ;
			count++;
		}
		// Check backward
		for (int k = 1; k < 4; k++)
		{
			nr = r - directions[d][0] * k;
			nc = c - directions[d][1] * k;
			if (nr < 0 || nr >= data->rows || nc < 0 || nc >= data->columns
				|| data->map[nr][nc] != symbol)
				break ;
			count++;
		}
		if (count >= 4)
			return (1);
	}
	return (0);
}

// Only consider columns that are adjacent to existing pieces.
// static int is_candidate_column(t_data *data, int col)
// {
//     // If board is empty, center is candidate
//     int center = data->columns / 2;
//     //if (data->map[data->rows-1][center] == '.') {
//         // Very basic check for empty board state if needed,
//
// but generally we check if any neighbor cols have pieces so idk if useful or needed
//     //}

//     // Look at col-2 to col+2. If any piece exists in bottom row,
//      this is a played area
//     int start;
//     int end;

//     if (col - 2 < 0)
//         start = 0;
//     else
//         start = col - 2;

//     if (col + 2 >= data->columns)
//         end = data->columns - 1;
//     else
//         end = col + 2;
//     for (int c = start; c <= end; c++) {
//         if (data->map[data->rows - 1][c] != '.') return (1);
//     }
//     if (col == center) return (1);

//     return (0);
// }

static int	minimax(t_data *data, int depth, int alpha, int beta, int is_max,
		int last_r, int last_c)
{
	int			min_search;
	t_bounds	b;
	int			max_eval;
	int			r;
	int			eval;
	int			min_eval;
	int			max_search;

	min_search = 0;
	if (last_r != -1)
	{
		if (!is_max && is_winning_move(data, last_r, last_c, '1'))
			return (10000000 + depth);
		if (is_max && is_winning_move(data, last_r, last_c, '2'))
			return (-10000000 - depth);
	}
	if (depth == 0)
		return (score_position(data));
	// Quick bounds calc for this node
	min_search = 0, max_search = data->columns;
	get_board_bounds(data, &b);
	min_search = b.min_c;
	max_search = b.max_c + 1; // +1 for loop operator <
	// Move ordering: Center outwards based on window
	// int window_width = max_search - min_search;
	// int center_window = min_search + window_width / 2;
	// linear scan from min_search to max_search
	if (is_max)
	{
		max_eval = INT_MIN;
		for (int c = min_search; c < max_search; c++)
		{
			// Skip if full
			if (data->map[0][c] != '.')
				continue ;
			r = get_available_row(data, c);
			data->map[r][c] = '1';
			eval = minimax(data, depth - 1, alpha, beta, 0, r, c);
			data->map[r][c] = '.';
			if (eval > max_eval)
				max_eval = eval;
			if (eval > alpha)
				alpha = eval;
			if (beta <= alpha)
				break ;
		}
		return ((max_eval == INT_MIN) ? 0 : max_eval);
	}
	else
	{
		min_eval = INT_MAX;
		for (int c = min_search; c < max_search; c++)
		{
			if (data->map[0][c] != '.')
				continue ;
			r = get_available_row(data, c);
			data->map[r][c] = '2';
			eval = minimax(data, depth - 1, alpha, beta, 1, r, c);
			data->map[r][c] = '.';
			if (eval < min_eval)
				min_eval = eval;
			if (eval < beta)
				beta = eval;
			if (beta <= alpha)
				break ;
		}
		return ((min_eval == INT_MAX) ? 0 : min_eval);
	}
}

// static int	get_safe_depth(t_data *data)
// {
// 	int	filled;

// 	// Total playable slots compared to branching factor
// 	// 20x40 or 90x200 on depth > 6 is suicide
// 	filled = 0;
// 	// check center column fill for approximation
// 	for (int r = 0; r < data->rows; r++)
// 		if (data->map[r][data->columns / 2] != '.')
// 			filled++;
// 	if (data->columns > 50)
// 		return (4); // Hard cap for wide boards
// 	if (filled < 4)
// 		return (6);
// 	return (5);
// }

static int	get_dynamic_depth(t_data *data)
{
	float	fill_ratio;
	int		total_cells;
	int		playable_cols;
	int		pieces_placed;
	int		depth;
	char	**map;

	map = data->map;
	total_cells = data->rows * data->columns;
	playable_cols = 0;
	pieces_placed = 0;
	// Find playable columns and approximate pieces placed
	for (int c = 0; c < data->columns; c++)
	{
		if (map[0][c] == '.')
			playable_cols++;
		// Find how many pieces are in each column to get total count
		for (int r = 0; r < data->rows; r++)
		{
			if (map[r][c] != '.')
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
}

void	ai_make_move(t_data *data)
{
	int best_score = INT_MIN;
	int best_col = -1;
	int target_row = -1;
	// int depth = get_safe_depth(data);
	int depth = get_dynamic_depth(data);

	// Calculate Search Window
	t_bounds b;
	get_board_bounds(data, &b);

	// Center of Action instead of board
	int action_center = (b.min_c + b.max_c) / 2;
	int width = b.max_c - b.min_c + 1;

	// array logic for the active window
	int *order = malloc(sizeof(int) * width);
	if (!order)
		return ; // Handle error

	for (int i = 0; i < width; i++)
	{
		if (i % 2 == 0)
			order[i] = action_center + (i / 2);
		else
			order[i] = action_center - (i / 2 + 1);
	}

	for (int i = 0; i < width; i++)
	{
		int c = order[i];
		if (c < 0 || c >= data->columns)
			continue ;
		if (c < b.min_c || c > b.max_c)
			continue ; // Should be covered but safety first ig

		int r = get_available_row(data, c);
		if (r != -1)
		{
			data->map[r][c] = '1';
			// If this move wins immediately, do it
			if (is_winning_move(data, r, c, '1'))
			{
				data->map[r][c] = '.';
				best_col = c;
				target_row = r;
				break ;
			}

			int score = minimax(data, depth - 1, INT_MIN, INT_MAX, 0, r, c);
			data->map[r][c] = '.';

			if (score > best_score || best_col == -1)
			{
				best_score = score;
				best_col = c;
				target_row = r;
			}
		}
	}

	free(order);

	if (best_col != -1)
	{
		data->map[target_row][best_col] = '1';
	}
}
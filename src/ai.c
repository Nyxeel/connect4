#include "../inc/connect4.h"
#include <limits.h>
#include <ncurses.h>

static int evaluate_window(int ai, int player, int empty)
{
    int score = 0;

    // AI Wins or is about to win
    if (ai == 4) return 100000;
    if (ai == 3 && empty == 1) score += 500;
    if (ai == 2 && empty == 2) score += 50;

    // Player threats (Must be blocked!)
    if (player == 3 && empty == 1) score -= 1000; 
    if (player == 2 && empty == 2) score -= 100;

    return score;
}

static int score_position(t_data *data)
{
    int score = 0;
    char **map = data->map;

    // 1. Center Column Preference, cause apparently good
    int center = data->columns / 2;
    for (int r = 0; r < data->rows; r++)
        if (map[r][center] == '1') score += 6;

    // 2. Sliding Window Scoring
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    
    for (int r = 0; r < data->rows; r++) {
        for (int c = 0; c < data->columns; c++) {
            for (int d = 0; d < 4; d++) {
                int dr = directions[d][0], dc = directions[d][1];
                int ai = 0, player = 0, empty = 0;

                for (int k = 0; k < 4; k++) {
                    int nr = r + dr * k, nc = c + dc * k;
                    if (nr >= 0 && nr < data->rows && nc >= 0 && nc < data->columns) {
                        if (map[nr][nc] == '1') ai++;
                        else if (map[nr][nc] == '2') player++;
                        else empty++;
                    } else {
                        ai = -1; // Out of bounds
                        break;
                    }
                }
                if (ai != -1) score += evaluate_window(ai, player, empty);
            }
        }
    }
    return score;
}

static int get_available_row(t_data *data, int col)
{
    for (int r = data->rows - 1; r >= 0; r--)
        if (data->map[r][col] == '.') return r;
    return -1;
}

static int is_winning_move(t_data *data, int r, int c, char symbol)
{
    int dirs[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    for (int i = 0; i < 4; i++) {
        int count = 1;
        for (int dir = -1; dir <= 1; dir += 2) {
            int dr = dirs[i][0] * dir, dc = dirs[i][1] * dir;
            int nr = r + dr, nc = c + dc;
            while (nr >= 0 && nr < data->rows && nc >= 0 && nc < data->columns && data->map[nr][nc] == symbol) {
                count++;
                nr += dr; nc += dc;
            }
        }
        if (count >= 4) return 1;
    }
    return 0;
}

static int minimax(t_data *data, int depth, int alpha, int beta, int is_maximizing, int last_r, int last_c)
{
    // Check if the move that led here ended the game
    if (last_r != -1) {
        if (!is_maximizing && is_winning_move(data, last_r, last_c, '1')) return 1000000 + depth;
        if (is_maximizing && is_winning_move(data, last_r, last_c, '2')) return -1000000 - depth;
    }
    if (depth == 0) return score_position(data);

    if (is_maximizing) {
        int max_eval = INT_MIN;
        for (int c = 0; c < data->columns; c++) {
            int r = get_available_row(data, c);
            if (r != -1) {
                data->map[r][c] = '1';
                int eval = minimax(data, depth - 1, alpha, beta, 0, r, c);
                data->map[r][c] = '.'; // Backtrack
                if (eval > max_eval) max_eval = eval;
                if (eval > alpha) alpha = eval;
                if (beta <= alpha) break;
            }
        }
        return (max_eval == INT_MIN) ? 0 : max_eval; // 0 for draw
    } else {
        int min_eval = INT_MAX;
        for (int c = 0; c < data->columns; c++) {
            int r = get_available_row(data, c);
            if (r != -1) {
                data->map[r][c] = '2';
                int eval = minimax(data, depth - 1, alpha, beta, 1, r, c);
                data->map[r][c] = '.'; // Backtrack
                if (eval < min_eval) min_eval = eval;
                if (eval < beta) beta = eval;
                if (beta <= alpha) break;
            }
        }
        return (min_eval == INT_MAX) ? 0 : min_eval;
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
} */

void ai_make_move(t_data *data)
{
    int best_score = INT_MIN;
    int best_col = -1;
    int target_row = -1;
    int depth = get_dynamic_depth(data); // Static or Dynamic depth

    // Column ordering: start from center for better pruning efficiency
    int order[data->columns];
    int mid = data->columns / 2;
    for (int i = 0; i < data->columns; i++) {
        order[i] = mid + ((i % 2 == 0) ? (i / 2) : -(i / 2 + 1));
        if (order[i] < 0 || order[i] >= data->columns) { /* handle edge cases if board is odd/even */ }
    }

    for (int i = 0; i < data->columns; i++) {
        int c = order[i];
        if (c < 0 || c >= data->columns) continue;
        
        int r = get_available_row(data, c);
        if (r != -1) {
            // FIX: Simulate the move before calling minimax!
            data->map[r][c] = '1';
            int score = minimax(data, depth - 1, INT_MIN, INT_MAX, 0, r, c);
            data->map[r][c] = '.'; // Clear move

            if (score > best_score || best_col == -1) {
                best_score = score;
                best_col = c;
                target_row = r;
            }
        }
    }

    if (best_col != -1)
        data->map[target_row][best_col] = '1';
}

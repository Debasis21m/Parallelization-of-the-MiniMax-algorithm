#include "board.h"

// EURISTHIC: win as fast as we can
int get_score(board_t* board, int depth, symbol_t symbol) {
	symbol_t result = winner(board);
	
	if(result == symbol) {
		return N * M + 10 - depth;
	} else if(result != EMPTY && result != NO_WINNER) {
		return -(N * M) - 10 + depth;
	} else if(result == NO_WINNER) {
		return 1;
	}

	return 0;
}

int move(board_t* board, symbol_t symbol, int depth, int alpha, int beta) {
	int n, i;
	move_t* max_move;
	int score = get_score(board, depth, symbol);

	if(score != 0) {
		return score;
	}

	move_t** moves = get_all_possible_moves(board, symbol, &n);
	for(i = 0; i < n; i++) {
		put_symbol(board, symbol, moves[i]);
		score = -move(board, other_symbol(symbol), depth + 1, -beta, -alpha);
		clear_symbol(board, moves[i]);

		if(score > alpha) {
			alpha = score;
			max_move = moves[i];
		}

		if(alpha >= beta) {
			break;
		}
	}

	if(depth == 0) {
		put_symbol(board, symbol, max_move);
	}

	for(i = 0; i < n; i++) {
		free(moves[i]);
	}

	free(moves);
	return alpha;
}

int main(int argc, char* argv[]) {
	
	board_t* board = create_board();
	symbol_t result;
	symbol_t current_symbol = X;

	move_t m;
 	m.i = 1;
	m.j = 1;
	//put_symbol(board, 0, &m);

	//print_board(board);

	while(1) {
		printf("Player %i to move next\n", (int) current_symbol);
		move(board, current_symbol, 0, -9999, 9999);
	//	print_board(board);
		result = winner(board);
	
		if(result != EMPTY) {
			break;
		}

		current_symbol = 1 - current_symbol;
	}

	printf("Winner: %i\n:", (int) result);

	return 0;
}

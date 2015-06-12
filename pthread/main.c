#include "board.h"
#include <pthread.h>

int move(board_t* board, symbol_t symbol, int depth, int alpha, int beta);

int global_n, next_free_move;
move_t** global_moves;
int global_max_score;
move_t* global_max_move;
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
board_t* global_board;
symbol_t global_symbol;

int NUM_THREADS = 1;

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

void* thread_compute_func(void* arg) {
	int thread_id = ((long int) arg);
	int i, score;
	int max_score;
	
	while(1) {

		pthread_mutex_lock(&mutex1);

		if(next_free_move >= global_n) {
			pthread_mutex_unlock(&mutex1);
			break;
		}

		i = next_free_move;
		next_free_move++;
		pthread_mutex_unlock(&mutex1);

		printf("thread %i computes move %i\n", thread_id, i);

		board_t* board = clone_board(global_board);
		put_symbol(board, global_symbol, global_moves[i]);
		
		pthread_mutex_lock(&mutex2);
		max_score = global_max_score;
		pthread_mutex_unlock(&mutex2);
		
		score = -move(board, other_symbol(global_symbol), 1, -9999, -max_score);

		free(board);

		pthread_mutex_lock(&mutex2);
		if(score > global_max_score) {
			global_max_score = score;
			global_max_move = global_moves[i];
		}
		pthread_mutex_unlock(&mutex2);
	}
	printf("thread %i finished\n", thread_id);
	return 0;
}

int move(board_t* board, symbol_t symbol, int depth, int alpha, int beta) {
	int n, i;
	int score = get_score(board, depth, symbol);
	move_t* max_move;

	if(score != 0) {
		return score;
	}

	move_t** moves = get_all_possible_moves(board, symbol, &n);
	if(depth == 0) {
		pthread_t threads[NUM_THREADS];
		global_moves = moves;
		global_max_score = -9999;
		next_free_move = 0;
		global_board = board;
		global_symbol = symbol;
		global_n = n;

		for (i = 0; i < NUM_THREADS; i++) {
			pthread_create(&threads[i], NULL, thread_compute_func, (void*) (long int)i);
		}

		for (i = 0; i < NUM_THREADS; i++) {
			pthread_join(threads[i], NULL);
		}
	
		printf("join completed\n");

		max_move = global_max_move;
		alpha = global_max_score;
	} else {
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

	if(argc < 2) {
		printf("Usage: %s <N_THREADS>\n", argv[0]);
		return -1;
	}

	NUM_THREADS = atoi(argv[1]);
	
//	print_board(board);
	pthread_mutex_init ( &mutex1, NULL);
	pthread_mutex_init ( &mutex2, NULL);

	while(1) {
		printf("Player %i to move next\n", (int) current_symbol);
		move(board, current_symbol, 0, -9999, 9999);
		print_board(board);
		result = winner(board);
	
		if(result != EMPTY) {
			break;
		}

		current_symbol = 1 - current_symbol;
	}

	printf("Winner: %i\n:", (int) result);

	return 0;
}

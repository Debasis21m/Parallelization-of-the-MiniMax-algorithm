#ifndef __BOARD_DEF

#define __BOARD_DEF
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define X 1
#define EMPTY 10
#define NO_WINNER 20

#define N 4
#define M N

typedef unsigned char symbol_t;

typedef struct board {
	symbol_t m[N][M];
	unsigned short n_empty;
} board_t;

typedef struct move {
	unsigned short i, j;
} move_t;

board_t* create_board();
void put_symbol(board_t*, symbol_t, move_t*);
void clear_symbol(board_t*, move_t*);
symbol_t winner(board_t*);
void print_board(board_t*);
move_t** get_all_possible_moves(board_t*, symbol_t, int*);
symbol_t other_symbol(symbol_t);
board_t* clone_board(board_t*);

#endif

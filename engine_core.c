#include "engine_core.h"
#include <stdio.h>



char board[8][8];
char score[2] = {2,2};
char turn;
extern move new;
move valid_moves[MAX_NUM_SQ];
move directions[8] = {{.i =  1, .j = 0}, {.i = -1, .j =  0},
			     {.i =  1, .j = 1}, {.i =  1, .j = -1},
			     {.i =  0, .j = 1}, {.i =  0, .j = -1},
			     {.i = -1, .j = 1}, {.i = -1, .j = -1}};

void init_board(void) {
  for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++){
      board[i][j] = NIL;
    }
  }
  board[3][4] = BLACK;
  board[4][3] = BLACK;
  board[3][3] = WHITE;
  board[4][4] = WHITE;

  turn = WHITE;
}

int check(move square, move direction) {
  char opponent = 3 - turn;
  int flipped = 0;
  for (int a = 1; a <= 8; a++) {
    char x = square.i + a*direction.i;
    char y = square.j + a*direction.j;
    if (x == -1 || y == -1 || x == 8 || y == 8 || board[x][y] == NIL) {
      return 0;
    }
    if (board[x][y] == turn) {
      return flipped;
    }
    if (board[x][y] == opponent) {
      flipped++;
    }
  }
  fprintf(stderr, "\n\n\nsomething's wrong, program should not be here!!!\n\n\n");
}

void flip(move square, move direction) {
  if (check(square, direction) != 0) {
    char opponent = 3 - turn;
    for (int a=1; a<8; a++) {
      char x = square.i + a*direction.i;
      char y = square.j + a*direction.j;
      if (x == -1 || y == -1 || x == 8 || y == 8 || board[x][y] == NIL) {
	fprintf(stderr, "\n\n\nsomething's wrong, this should not occur!!!\n\n\n");
	return;
      }
      if (board[x][y] == turn) {
	return;
      }
      if (board[x][y] == opponent) {
	board[x][y] = turn;
	score[turn-1]++;
	score[opponent-1]--;
      }
    }
  }
}

int execute_move(move square) {
  if (!is_valid(square)) {
    return 0;
  }
  fprintf(stderr, "engine entered exec_move\n");
  for (int a=0; a<8; a++) {
    move dir = directions[a];
    flip(square, dir);
  }
  board[square.i][square.j] = turn;
  score[turn-1]++;
  change_turn();
  return 1;
  
  
  fprintf(stderr, "engine leaving exec_move\n");
}

int check_square(move square) {
  int flipped = 0;
  for (int a = 0; a < 8; a++) {
    flipped += check(square, directions[a]);
  }
  return flipped;
}

int is_valid(move square) {
  return check_square(square)? 1: 0;
}

int find_valid_moves(void) {
  int c = 0;
  char opponent;
  if (turn == WHITE) opponent = BLACK;
  else opponent = WHITE;

  for (int a=0; a<MAX_NUM_SQ; a++) {
    valid_moves[a].i = -1;
    valid_moves[a].j = -1;
  }
  for (int i=0; i<8; i++) {
    for (int j=0; j<8; j++) {
      move square = {.i = i, .j = j};
      if (board[i][j] == NIL && check_square(square) > 0) {
	valid_moves[c].i = i;
	valid_moves[c].j = j;
	c++;
      }
    }
  }
  return c;
}



void check_win(void) {
  /* char opponent = 3 - turn;
  if (score[opponent-1] == 0) {
    printf("%s wins!\n", turn-1? "white":"black");
    exit(0);
  }
  if (score[0]+score[1] == 64) {
    if (score[0] == score[1]) {
      printf("the game is a draw!\n");
    } else {
      printf("%s wins!\n", (score[0]-score[1] < 0)? "white": "black");
    }
    exit(0);
    }*/
}

void change_turn(void) {
  turn = 3 - turn;
}


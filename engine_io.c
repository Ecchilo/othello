#include <stdio.h>
#include "engine_core.h"
#include "engine_io.h"

move new;
extern char turn;
extern char board[8][8];


void rec_move(void) {
  fprintf(stderr, "engine entered rec_move\n");
  char s[2];
  scanf("%s", s);
  new.i = s[0] - '0';
  new.j = s[1] - '0';
  fprintf(stderr, "engine received: %d%d\n", new.i, new.j);  
}

void send_position(void) {
  char pos[66];
  pos[0] = '0' + turn;
  for (int i=0; i<=7; i++) {
    for (int j=0; j<=7; j++) {
      pos[8*i+j + 1] = '0' + board[i][j];
    }
  }
  pos[65] = '\0';
  printf("%s\n", pos);
  fflush(stdout);
  fprintf(stderr, "%s\nsent from engine\n", pos);
}

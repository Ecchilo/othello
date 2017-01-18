#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "engine_core.h"
#include "engine_io.h"

extern move new;
extern char turn;



void mainloop(void) {
  fprintf(stderr, "engine entered mainloop\n");
  while (1) {
    if (find_valid_moves()) {
      fprintf(stderr, "engine will get move\n");
      rec_move();
      fprintf(stderr, "engine has move, will move\n");
      execute_move(new);
      fprintf(stderr, "engine has moved\n");
      send_position();
      fprintf(stderr, "engine sent position\n");
    } else {
      fprintf(stderr, "no moves available for %s. passing.\n", turn-1?"white":"black");
      change_turn();
    }
  }
}


int main(int argc, char** argv) {
  fprintf(stderr, "engine started\n");
  init_board();
  fprintf(stderr, "engine will send initial position\n");
  send_position();
  fprintf(stderr, "engine just sent initial position\n");
  mainloop();
  return 0;
}

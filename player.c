#include <stdio.h>
#include "player_io.h"
#include "engine_core.h"

char move[2];

void evaluate();


int main() {
  fprintf(stderr, "player started\n");
  while (1) {
    read_position();
    evaluate();
    send_move(move);
  }
  return 0;
}

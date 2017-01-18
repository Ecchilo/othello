#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char position[66];
char move[3];

int pipe_a_w[2]; /* pipe from adapter to white */
int pipe_a_b[2]; /* pipe from adapter to black */

int pipe_wb_a[2]; /* pipe from players to adapter */
int pipe_a_e[2]; /* pipe from adapter to engine */
int pipe_e_a[2]; /* pipe from engine to adapter */


void engine2players() {
  fprintf(stderr, "adapter passing position to players\n");
  int r = read(pipe_e_a[0], position, sizeof(position));
  fprintf(stderr, "adapter: read %d bytes\n", r);
  position[65] = '\n';
 
  fprintf(stderr, "adapter read position: %s", position);
  write(pipe_a_w[1], position, sizeof(position));
  write(pipe_a_b[1], position, sizeof(position));
}

void white2engine() {
  fprintf(stderr, "adapter passing white move to engine\n");
  read(pipe_wb_a[0], move, sizeof(move));
  move[2] = '\n';
 
  fprintf(stderr, "adapter read white move: %s\n", move);
  write(pipe_a_e[1], move, sizeof(move));
}

void black2engine() {
  fprintf(stderr, "adapter passing black move to engine\n");
  read(pipe_wb_a[0], move, sizeof(move));
  move[2] = '\n';
 
  fprintf(stderr, "adapter read black move: %s\n", move);
  write(pipe_a_e[1], move, sizeof(move));
}





int main(void) {

  pipe(pipe_a_w);
  pipe(pipe_a_b);

 
 
  pipe(pipe_wb_a);
 

 
  pipe(pipe_a_e);
  pipe(pipe_e_a);
 
  if (fork()==0) {
    /* first child: the engine e */
    close(0);
    dup(pipe_a_e[0]); /*stdin of e is pipe_a_e[0]*/
    close(pipe_a_e[0]);
    
    close(1);
    dup(pipe_e_a[1]); /*stdout of e is pipe_e_a[1]*/
    close(pipe_e_a[1]);

    fprintf(stderr, "engine process\n");

    execlp("./engine", "engine", NULL);
  } else if (fork()==0) {
    /* second child: white w */
    close(0);
    dup(pipe_a_w[0]); /*stdin of w is pipe_a_w[0]*/
    close(pipe_a_w[0]);
    
    close(1);
    dup(pipe_wb_a[1]); /*stdout of w is pipe_wb_a[1]*/
    close(pipe_wb_a[1]);

    fprintf(stderr, "white process\n");

    execlp("./board.tcl", "board.tcl", "white", NULL);
  } else if (fork()==0) {
        /* third child: black b  */
    close(0);
    dup(pipe_a_b[0]); /*stdin of b is pipe_a_b[0]*/
    close(pipe_a_b[0]);
    
    close(1);
    dup(pipe_wb_a[1]); /*stdout of b is pipe_wb_a[1]*/
    close(pipe_wb_a[1]);

    fprintf(stderr, "black process\n");

    execlp("./board.tcl", "board.tcl", "black", NULL);
  } else {
    /* this is the parent: adapter a */
    /* closes ends of pipes away from a */
    close(pipe_e_a[1]);
   
    close(pipe_wb_a[1]);
    close(pipe_a_e[0]);
    close(pipe_a_w[0]);
    close(pipe_a_b[0]);
    fprintf(stderr, "adapter process\n");
    /* enters mainloop: organizing communication */
    /* between players and engine                */
    int counter = 0;
    while(1) {
      fprintf(stderr, "adapter entered loop #%d\n", counter);
      engine2players();
      fprintf(stderr, "in adapter, position is: %s\n", position);
      if (counter % 2 == 0) {
	white2engine();
	fprintf(stderr, "adapter: white move is %s\n", move);
      } else {
	black2engine();
	fprintf(stderr, "adapter: black move is %s\n", move);
      }
      counter++;
    }
  }
  return 0;
}

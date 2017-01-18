#define MAX_NUM_SQ 64
#define NIL 0
#define BLACK 1
#define WHITE 2

typedef struct {char i; char j;} move;





void init_board(void);

int check(move, move);

void flip(move, move);

int execute_move(move);

int check_square(move);

int is_valid(move);

int find_valid_moves(void);



void check_win(void);

void change_turn(void);




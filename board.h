#ifndef _BOARD_H
#define _BOARD_H

struct pos {
    unsigned int r;
    unsigned int c;
};

typedef struct pos pos;

pos make_pos(unsigned int r, unsigned int c);

pos add_pos(pos pos_1, pos pos_2);

struct square {
    char entry;
    int* option;
};

typedef struct square square;

typedef square** board;

board* board_new();

void board_free(board* b);

void board_show(board* b);

square board_get(board* b, pos p);

void board_set(board* b, pos p, char c);

board* board_cpy(board* b);

#endif /* _BOARD_H */

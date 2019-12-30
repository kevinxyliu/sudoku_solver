#ifndef _SOLVE_H
#define _SOLVE_H

pos* first_empty(board* b);

board* new_board(board* b, pos* p, char entry);

int rule_1(board* b);

int rule_2(board* b);

board* solve(board* b);

int check(board* b);

#endif /* _BOARD_H */

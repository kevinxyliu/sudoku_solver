#include <stdlib.h>
#include <stdio.h>
#include "board.h"

pos make_pos(unsigned int r, unsigned int c)
{
    pos res = {r,c};
    return res;
}

pos add_pos(pos pos_1, pos pos_2)
{
    pos res = {pos_1.r + pos_2.r, pos_1.c + pos_2.c};
    return res;
}

board* board_new()
{
    board* res = (board*)malloc(sizeof(board));
    *res = (square**)malloc(9 * sizeof(square*));
    for (unsigned int i = 0; i < 9; i++) {
        (*res)[i] = (square*)malloc(9 * sizeof(square));
        for (unsigned int j = 0; j < 9; j++) {
            (*res)[i][j].entry = 0;
            (*res)[i][j].option = (int*)malloc(9 * sizeof(int));
            for (unsigned int k = 0; k < 9; k++) {
                (*res)[i][j].option[k] = 1;
            }
        }
    }
    return res;
}

void board_free(board* b)
{
    for (unsigned int i = 0; i < 9; i++) {
        for (unsigned int j = 0; j < 9; j++) {
            free((*b)[i][j].option);
        }
        free((*b)[i]);
    }
    free(*b);
    free(b);
}

void entry_show(board* b, pos p)
{
    square res = board_get(b,p);
    if (res.entry == 0) {
        printf("_");
    } else {
        printf("%d", res.entry);
    }
}

void row_show(board* b, unsigned int r)
{
    for (unsigned int i = 0; i < 9; i++) {
        entry_show(b, make_pos(r,i));
    }
    printf("\n");
}

void board_show(board* b)
{
    for (unsigned int i = 0; i < 9; i++) {
        row_show(b,i);
    }
}

square board_get(board* b, pos p)
{
    if (p.r >= 9 || p.c >= 9) {
        fprintf(stderr, "board_get: the position is outside the board\n");
        exit(1);
    }
    return (*b)[p.r][p.c];
}

void board_set(board* b, pos p, char c)
{
    if (p.r >= 9 || p.c >= 9) {
        fprintf(stderr, "board_set: the position is outside the board\n");
        exit(1);
    }
    if (c == 0 || board_get(b,p).entry != 0) {
        board* cpy = board_cpy(b);
        (*cpy)[p.r][p.c].entry = c;
        *b = *board_new();
        for (unsigned int m = 0; m < 9; m++) {
            for (unsigned int n = 0; n < 9; n++) {
                if (board_get(cpy,make_pos(m,n)).entry != 0) {
                    board_set(b,make_pos(m,n),board_get(cpy,make_pos(m,n)).entry);
                }
            }
        }
        return;
    }
    (*b)[p.r][p.c].entry = c;
    for (unsigned int k = 0; k < 9; k++) {
        (*b)[p.r][p.c].option[k] = 0;
    }
    for (unsigned int i = 0; i < 9; i++) {
        (*b)[i][p.c].option[c-1] = 0;
        (*b)[p.r][i].option[c-1] = 0;
    }
    int row_quotient = p.r/3;
    int col_quotient = p.c/3;
    pos square[9] = {{0,0},{0,3},{0,6},{3,0},{3,3},{3,6},{6,0},{6,3},{6,6}};
    pos single[9] = {{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}};
    pos upperleft = square[row_quotient * 3 + col_quotient];
    for (unsigned int j = 0; j < 9; j++) {
        board_get(b,add_pos(upperleft,single[j])).option[c-1] = 0;
    }
}

board* board_cpy(board* b)
{
    board* res = (board*)malloc(sizeof(board));
    (*res) = (square**)malloc(9 * sizeof(square*));
    for (unsigned int i = 0; i < 9; i++) {
        (*res)[i] = (square*)malloc(9 * sizeof(square));
        for (unsigned int j = 0; j < 9; j++) {
            (*res)[i][j].entry = (*b)[i][j].entry;
            (*res)[i][j].option = (int*)malloc(9 * sizeof(int));
            for (unsigned int k = 0; k < 9; k++) {
                (*res)[i][j].option[k] = (*b)[i][j].option[k];
            }
        }
    }
    return res;
}

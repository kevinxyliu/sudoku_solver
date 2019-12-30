#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "solve.h"

pos* first_empty(board* b)
{
    pos* res = (pos*)malloc(sizeof(pos));
    for (unsigned int i = 0; i < 9; i++) {
        for (unsigned int j = 0; j < 9; j++) {
            if (board_get(b,make_pos(i,j)).entry == 0) {
                res->r = i;
                res->c = j;
                return res;
            }
        }
    }
    free(res);
    return NULL;
}

board* new_board(board* b, pos* p, char entry)
{
    board* res = board_cpy(b);
    if (p != NULL) {
        board_set(res, make_pos(p->r,p->c), entry);
    }
    return res;
}

int rule_1_aux(board* b, pos p)
{
    int num_of_options = 0;
    for (unsigned int i = 0; i < 9; i++) {
        if (board_get(b,p).option[i] == 1) {
            num_of_options++;
        }
    }
    if (num_of_options == 0 && board_get(b,p).entry == 0) {
        return -1;
    }
    if (num_of_options == 1) {
        for (unsigned int j = 0; j < 9; j++) {
            if (board_get(b,p).option[j] == 1) {
                board_set(b,p,j+1);
                return 1;
            }
        }
    }
    return 0;
}

int rule_1(board* b)
{
    for (unsigned int i = 0; i < 9; i++) {
        for (unsigned int j = 0; j < 9; j++) {
            if (rule_1_aux(b,make_pos(i,j)) == -1) {
                return -1;
            }
            if (rule_1_aux(b,make_pos(i,j)) == 1) {
                return 1;
            }
        }
    }
    return 0;
}

int rule_2_row(board* b, unsigned int i)
{
    int appear[9] = {0};
    for (unsigned int j = 0; j < 9; j++) {
        for (unsigned int k = 0; k < 9; k++) {
            if (board_get(b,make_pos(i,j)).option[k] == 1) {
                appear[k]++;
            }
        }
    }
    int filled[9] = {0};
    for (unsigned int s = 0; s < 9; s++) {
        if (board_get(b,make_pos(i,s)).entry != 0) {
            filled[board_get(b,make_pos(i,s)).entry-1] = 1;
        }
    }
    int smallest_one = -1;
    for (unsigned int m = 0; m < 9; m++) {
        if (appear[m] == 0 && filled[m] == 0) {
            return -1;
        }
        if (appear[m] == 1) {
            smallest_one = m;
        }
    }
    if (smallest_one == -1) {
        return 0;
    }
    for (unsigned int n = 0; n < 9; n++) {
        if (board_get(b,make_pos(i,n)).option[smallest_one] == 1) {
            board_set(b,make_pos(i,n),smallest_one+1);
            return 1;
        }
    }
    return 0;
}

int rule_2_col(board* b, unsigned int i)
{
    int appear[9] = {0};
    for (unsigned int j = 0; j < 9; j++) {
        for (unsigned int k = 0; k < 9; k++) {
            if (board_get(b,make_pos(j,i)).option[k] == 1) {
                appear[k]++;
            }
        }
    }
    int filled[9] = {0};
    for (unsigned int s = 0; s < 9; s++) {
        if (board_get(b,make_pos(s,i)).entry != 0) {
            filled[board_get(b,make_pos(s,i)).entry-1] = 1;
        }
    }
 
    int smallest_one = -1;
    for (unsigned int m = 0; m < 9; m++) {
        if (appear[m] == 0 && filled[m] == 0) {
            return -1;
        }
        if (appear[m] == 1) {
            smallest_one = m;
        }
    }
    if (smallest_one == -1) {
        return 0;
    }
    for (unsigned int n = 0; n < 9; n++) {
        if (board_get(b,make_pos(n,i)).option[smallest_one] == 1) {
            board_set(b,make_pos(n,i),smallest_one+1);
            return 1;
        }
    }
    return 0;
}

int rule_2_sqr(board* b, unsigned int i)
{
    pos square[9] = {{0,0},{0,3},{0,6},{3,0},{3,3},{3,6},{6,0},{6,3},{6,6}};
    pos single[9] = {{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}};
    int appear[9] = {0};
    for (unsigned int j = 0; j < 9; j++) {
        for (unsigned int k = 0; k < 9; k++) {
            if (board_get(b,add_pos(square[i],single[j])).option[k] == 1) {
                appear[k]++;
            }
        }
    }
    int filled[9] = {0};
    for (unsigned int s = 0; s < 9; s++) {
        if (board_get(b,add_pos(square[i],single[s])).entry != 0) {
            filled[board_get(b,add_pos(square[i],single[s])).entry-1] = 1;
        }
    }
    int smallest_one = -1;
    for (unsigned int m = 0; m < 9; m++) {
        if (appear[m] == 0 && filled[m] == 0) {
            return -1;
        }
        if (appear[m] == 1) {
            smallest_one = m;
        }
    }
    if (smallest_one == -1) {
        return 0;
    }
    for (unsigned int n = 0; n < 9; n++) {
        if (board_get(b,add_pos(square[i],single[n])).option[smallest_one] == 1) {
            board_set(b,add_pos(square[i],single[n]),smallest_one+1);
            return 1;
        }
    }
    return 0;
}

int rule_2(board* b)
{
    for (unsigned int i = 0; i < 9; i++) {
        int res_row = rule_2_row(b,i);
        if (res_row == 1) {
            return 1;
        } else if (res_row == -1) {
            return -1;
        }
        int res_col = rule_2_col(b,i);
        if (res_col == 1) {
            return 1;
        } else if (res_col == -1) {
            return -1;
        }
        int res_sqr = rule_2_sqr(b,i);
        if (res_sqr == 1) {
            return 1;
        } else if (res_sqr == -1) {
            return -1;
        }
    }
    return 0;
}

board* solve(board* b)
{
    if (check(b) == 0) {
        return NULL;
    }
    while (1) {
        int res_1 = rule_1(b);
        int res_2 = rule_2(b);
        if (res_1 == -1 || res_2 == -1) {
            return NULL;
        }
        if (res_1 == 0 && res_2 == 0) {
            break;
        }
    }
    pos* empty_entry = first_empty(b);
    if (empty_entry == NULL) {
        return b;
    }
    for (unsigned int i = 0; i < 9; i++) {
        if (board_get(b, make_pos(empty_entry->r,empty_entry->c)).option[i] == 1) {
            board* board_aux = new_board(b, empty_entry, i+1);
            board* res_aux = solve(board_aux);
            if (res_aux != NULL) {
                return res_aux;
            }
            board_free(board_aux);
        }
    }
    return NULL;
}

int check_row(board* b)
{
    for (unsigned int i = 0; i < 9; i++) {
        int array[9] = {0};
        for (unsigned int j = 0; j < 9; j++) {
            char entry = board_get(b, make_pos(i,j)).entry;
            if (entry != 0) {
                if (array[entry-1] == 1) {
                    return 0;
                }
                array[entry-1] = 1;
            }
        }
    }
    return 1;
}

int check_col(board* b)
{
    for (unsigned int i = 0; i < 9; i++) {
        int array[9] = {0};
        for (unsigned int j = 0; j < 9; j++) {
            char entry = board_get(b, make_pos(j,i)).entry;
            if (entry != 0) {
                if (array[entry-1] == 1) {
                    return 0;
                }
                array[entry-1] = 1;
            }
        }
    }
    return 1;
}

int check_sqr(board* b)
{
    pos square[9] = {{0,0},{0,3},{0,6},{3,0},{3,3},{3,6},{6,0},{6,3},{6,6}};
    pos single[9] = {{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}};
    for (unsigned int i = 0; i < 9; i++) {
        int array[9] = {0};
        for (unsigned int j = 0; j < 9; j++) {
            char entry = board_get(b, add_pos(square[i],single[j])).entry;
            if (entry != 0) {
                if (array[entry-1] == 1) {
                    return 0;
                }
                array[entry-1] = 1;
            }
        }
    }
    return 1;
}

int check(board* b)
{
    return check_row(b) && check_col(b) && check_sqr(b);
}

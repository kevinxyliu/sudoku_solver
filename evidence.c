#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "time.h"

void show_option(board* b, pos p)
{
    for (unsigned int i = 0; i < 9; i++) {
        if (board_get(b,p).option[i] == 1) {
            printf("%d ",i+1);
        }
    }
    printf("\n");
}

int main(int argc, char** argv)
{
    board* test = board_new();
    board_set(test,make_pos(0,0),1);
    show_option(test,make_pos(0,0));
    show_option(test,make_pos(0,1));
    show_option(test,make_pos(1,0));
    show_option(test,make_pos(0,8));
    show_option(test,make_pos(3,3));
    return 0;
}


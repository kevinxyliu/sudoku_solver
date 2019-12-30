#include <stdlib.h>
#include <stdio.h>
#include "board.h"
#include "solve.h"
#include <string.h>

void start_game()
{
    printf("*** Welcome to Sudoku! ***\n");
    printf("Instructions: To enter a number at a specific position, specify"
           " the position\nfirst (e.g. 11 is the top left corner, 99 is the"
           " bottom right corner) and then\nthe number (Enter 0 to remove "
           "the number at that position). Type \"F\"/\"f\" "
           "to\nfinish. The result will show up on the screen!\n");
}

pos scan_pos()
{
    char position[2];
    pos res;
    printf("Please enter a position on the board: ");
    scanf(" %s", position);
    if (strcmp(position,"F") == 0 || strcmp(position,"f") == 0) {
        res.r = 9;
        res.c = 9;
        return res;
    }
    while (!(position[0] >= '1' && position[0] <= '9'
        && position[1] >= '1' && position[1] <= '9')) {
        printf("The position is not valid! Try again.\n");
        printf("Please enter a position on the board: ");
        scanf(" %s", position);
        if (strcmp(position,"F") == 0 || strcmp(position,"f") == 0) {
            res.r = 9;
            res.c = 9;
            return res;
        }
    }
    res.r = atoi(position)/10 - 1;
    res.c = atoi(position + 1) - 1;
    return res;
}

char scan_num()
{
    char res;
    printf("Please enter a number: ");
    scanf(" %c", &res);
    while (!(res <= '9' && res >= '0')) {
        printf("The number is not valid! Try again.\n");
        printf("Please enter a number: ");
        scanf(" %c", &res);
    }
    return atoi(&res);
}

int final_check(board* b)
{
    board_show(b);
    printf("Is this the sudoku puzzle you want to solve? (yes/no) ");
    char res[4];
    scanf(" %s",res);
    while ((strcmp(res, "yes") != 0) && (strcmp(res, "no") != 0)) {
        printf("Invalid answer. Try again.\n");
        printf("Is this the sudoku puzzle you want to solve? (yes/no) ");
        scanf(" %s",res);
    }
    if (strcmp(res,"yes") == 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char** argv)
{
    start_game();
    board* b = board_new();
    pos position;
    char number;
    int bool = 0;
    while (bool == 0) {
        position.r = 0;
        while (position.r < 9) {
            position = scan_pos();
            if (position.r == 9) {
                break;
            } else {
                number = scan_num();
                board_set(b, position, number);
            }
        }
        bool = final_check(b);
    }
    board* res = solve(b);
    if (res == NULL) {
        printf("Your puzzle has no solution. \n");
    } else {
        printf("Here is the result:\n");
        board_show(res);
        board_free(res);
    }
    return 0;
}

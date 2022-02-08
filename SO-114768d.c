/*----------------------------------------------------------------------------
Project: stackoverflow puzzle "Jumping knights on a 5x5 grid"
Purpose: https://puzzling.stackexchange.com/questions/114768/jumping-knights-on-a-5x5-grid
Author : Copyright (C) Weather Vane
History: d-  Revert to ver b, clean up for posting
----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GRID        5
#define MOVES       8
#define MAXLEVEL    15
#define EMPTY       0
#define BLACK       1
#define WHITE       2
#define BOTH        3

char *sym[] = { ".", "B", "W", " " };
char *name[] = { "White", "Black" };
char newline[] = "<BR>";
int dx[MOVES] = { -1, -1, +1, +1, -2, -2, +2, +2 };
int dy[MOVES] = { -2, +2, -2, +2, -1, +1, -1, +1 };
unsigned char path[MAXLEVEL+1][GRID][GRID];
int hist[MAXLEVEL+1];
int gox[MAXLEVEL+1];
int goy[MAXLEVEL+1];
int tox[MAXLEVEL+1];
int toy[MAXLEVEL+1];
char *hdir[MOVES] = { "1 left", "1 left", "1 right", "1 right", "2 left", "2 left", "2 right", "2 right" };
char *vdir[MOVES] = { "2 up"  , "2 down", "2 up"  ,  "2 down",  "1 up"  , "1 down", "1 up",    "1 down"  };
unsigned result = 0;
char board[MAXLEVEL+1][GRID][GRID] = { {
    { EMPTY, BLACK, EMPTY, BLACK, EMPTY },
    { WHITE, BLACK, EMPTY, BLACK, EMPTY },
    { WHITE, EMPTY, WHITE, EMPTY, WHITE },
    { WHITE, BLACK, BLACK, EMPTY, WHITE },
    { BLACK, EMPTY, BLACK, WHITE, WHITE },
}, };

void show(void)
{
    printf(">! <pre>Using **%s** and **%s** for the **Black** and **White** Knights%s", sym[BLACK], sym[WHITE],
         newline);

    for(int level=0; level<=MAXLEVEL; level++) {
        if(level)
            printf("Move %d: **%s** from %c%c to %c%c%s", level, name[level & 1], 
                    'a' + gox[level], '1' + goy[level],
                    'a' + tox[level], '1' + toy[level],
                    newline);
        for(int i=GRID-1; i>=0; i--) {
            printf("%c  ", '1' + i);
            for(int j=0; j<GRID; j++) {
                printf("%s ", sym[ board[level][i][j] ]);
            }
            printf("%s", newline);
        }
        
        printf("   ");
        for(int j=0; j<GRID; j++) {
            printf("%c ", 'a' + j);
        }
        printf("%s", newline);
        printf("%s", newline);
    }
    printf("</pre>\n");
}

void recur(int level, int player)
{
    if(level > MAXLEVEL) {
        result++;
        //return;
        show();
        exit(0);
    }
    int other = player ^ BOTH;
    memcpy(board[level], board[level-1], GRID * GRID);
    for(goy[level]=0; goy[level]<GRID; goy[level]++) {
        for(gox[level]=0; gox[level]<GRID; gox[level]++) {
            if(board[level][goy[level]][gox[level]] == player) {
                board[level][goy[level]][gox[level]] = EMPTY;
                for(hist[level]=0; hist[level]<MOVES; hist[level]++) {
                    toy[level] = goy[level] + dy[hist[level]];
                    if(toy[level] >= 0 && toy[level] < GRID) {
                        tox[level] = gox[level] + dx[hist[level]];
                        if(tox[level] >= 0 && tox[level] < GRID) {
                            if(board[level][toy[level]][tox[level]] == other) {
                                board[level][toy[level]][tox[level]] = player;
                                recur(level + 1, other);
                                board[level][toy[level]][tox[level]] = other;
                            }
                        }
                    }
                }
                board[level][goy[level]][gox[level]] = player;
            }
        }
    }
}

int main(void)
{
    recur(1, BLACK);
    printf("result=%u\n", result);
    return 0;
}


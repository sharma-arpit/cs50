#define _XOPEN_SOURCE 500

#include<stdio.h>
#include<cs50.h>
#include <unistd.h>
#include <stdlib.h>
char board[3][3];

void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

void init()
{
    int i, j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            board[i][j] = '0';
        }
    }
}

bool win()
{
    int i=0, j=0;
    for(i=0;i<3;i++)
    {
        if (board[i][j] == board[i][j+1] && board[i][j+1] == board[i][j+2] && board[i][j] != '0')
        {
            return true;
        }
        else if(board[j][i] == board[j+1][i] && board[j+1][i] == board[j+2][i] && board[j][i] != '0')
        {
            return true;
        }
    }
return false;    
}

void draw()
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            printf("----");
        }
        printf("-\n");
        for(j=0;j<3;j++)
        {
            printf("|");
            if (board[i][j] != '0')
            {
                printf(" %c ", board[i][j]);
            }
            else
            {
                printf("   ");
            }
        }
        printf("|");
        printf("\n");
    }
    for(j=0;j<3;j++)
    {
        printf("----");
    }
    printf("-\n");
}

bool move(int row, int col, int i)
{
    if (row>2 || row<0 || col>2 || col<0)
    return false;
    if (i%2==0 && board[row][col] =='0') //when user 2
    {
        board[row][col] = 'o';
        return true;
    }
    else if(board[row][col] =='0') // when user 1
    {
        board[row][col] = 'x';
        return true;
    }
return false;
}

int main()
{
    int i=1, row, col;
    
    init();  // initialise the Game

    while(i)
    {
        clear();    // clear the terminal
        draw();     // draw the current state of the Game
        
        printf("\nYour Response: ");
        scanf("%d %d", &row, &col);
        if (row == 9 && col == 9)
        {
            printf("Okay!\n");
            break;
        }
        if (!move(row, col, i))
        {
            printf("Illegal move!\n");
            usleep(500000);
        }
        
        if (win())
        {
            clear();
            draw();
            if(i%2==0)
            {
                printf("Congratulations! User 2 has won the Game.\n");
            }
            else
            {
                printf("Congratulations! User 1 has won the Game.\n");
            }
            break;
        }
        usleep(500000);
        i++;
    }
    return 0;
}
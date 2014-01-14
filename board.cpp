#include <bitset>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "board.h"

using namespace std;
using namespace BoardSpace;


Board::Board(const char *conf)
{
    for (int i=0; i<9; i++)
    {
        if (conf[i] == '_')
            board[i] = 0;
        else
            // convert from ascii to decimal
            board[i] =  ((int)conf[i]) - 48;
    }
}

Board::Board(const int arrayboard[9])
{
    for (int i=0; i<9; i++)
        board[i] = arrayboard[i];
}

Board::Board(const int hash)
{
    int mhash = hash;
    for (int i=0; i<9; i++)
    {
        board[8-i] = mhash % 10;
        mhash /= 10;
    }

}


void Board::calcHash()
{
    hash = 0;
    for (int i=0; i<9; i++)
        hash = hash + board[8-i] * (int) pow(10.0, (double) i);
    
    return;
}


void Board::printPretty()
{
    for (int i=1; i<=9; i++)
    {
        printf("%d ", board[i-1]);
        if (i>1 && i%3 == 0)
            printf("\n");
    }
}


void Board::printConf()
{
    for (int i=0; i<9; i++)
    {
        if (board[i] == 0)
            printf("_");
        else
            printf("%d", board[i]);
    }
}

void Board::calcManhattan()
{
    manhattan = 0;
    for (int i=0; i<9; i++)
    {
        int xd = abs(getCol(i)-getCol(goalBoard[board[i]]));
        int yd = abs(getRow(i)-getRow(goalBoard[board[i]]));

        manhattan += xd + yd;
    }

}


int BoardSpace::getCol(int i)
{
    if (i == 0 || i == 3 || i == 6)
        return 1;
    if (i == 1 || i == 4 || i == 7)
        return 2;
    if (i == 2 || i == 5 || i == 8)
        return 3;

    return -1;
}

int BoardSpace::getRow(int i)
{
    if (i == 0 || i == 1 || i == 2)
        return 1;
    if (i == 3 || i == 4 || i == 5)
        return 2;
    if (i == 6 || i == 7 || i == 8)
        return 3;

    return -1;
}

void BoardSpace::swap(int* board, int src, int dest)
{
    int temp = board[dest];
    board[dest] = board[src];
    board[src] = temp;
}



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


// if top row and left column are correct send back 0
void Board::calcTopLeft()
{
    int top = 1; 
    int left =1;
    //int middlev =2;
    //int middleh =1;

    if (board[0] == 1 && board[1] == 2 && board[2] == 3)
        top = 0;

    if (board[0] == 1 && board[3] == 4 && board[6] == 7)
        left = 0;

    //if (board[1] == 2 && board[4] == 5 && board[7] == 8)
        //middlev = 0;

    //if (board[3] == 4 && board[4] == 5 && board[5] == 6)
        //middleh = 0;

    //topleft = top + left + middlev + middleh;
    topleft = top + left;
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

void Board::calcMisPlaced()
{
    misplaced = 0;
    for (int i=0; i<8; i++)
        if (board[i] != i+1)
                misplaced++;
    if (board[8] != 0)
        misplaced++;
}

void Board::calcFitness()
{
    fitness = 1 - getManhattan()*.01 - getMisPlaced()*.01;
    //fitness = 1 - getManhattan()*.01 - getTopLeft()*.01;
    //fitness = 1 - getManhattan()*.01;
}

void Board::calcMoves()
{
    int i;

    // clear moves
    for (i=0; i<4; i++)
        moves[i] = 0;

    // find zero spot
    for(i=0; i<9; i++)
        if (board[i] == 0) break;
    
    // to keep track of what move is on
    int j = 0;
    int *b = getBoard();
    switch (i)
    {
        case 0:
            swap(b, 0, 1);
            moves[j++] = Board(b).getHash();
            swap(b, 0, 1);
            swap(b, 0, 3);
            moves[j++] = Board(b).getHash();
            swap(b, 0, 3);
            break; 
        case 1:
            swap(b, 1, 0);
            moves[j++] = Board(b).getHash();
            swap(b, 1, 0);
            swap(b, 1, 2);
            moves[j++] = Board(b).getHash();
            swap(b, 1, 2);
            swap(b, 1, 4);
            moves[j++] = Board(b).getHash();
            swap(b, 1, 4);
            break;
        case 2:
            swap(b, 2, 1);
            moves[j++] = Board(b).getHash();
            swap(b, 2, 1);
            swap(b, 2, 5);
            moves[j++] = Board(b).getHash();
            swap(b, 2, 5);
            break;
        case 3:
            swap(b, 3, 0);
            moves[j++] = Board(b).getHash();
            swap(b, 3, 0);
            swap(b, 3, 4);
            moves[j++] = Board(b).getHash();
            swap(b, 3, 4);
            swap(b, 3, 6);
            moves[j++] = Board(b).getHash();
            swap(b, 3, 6);
            break;
        case 4:
            swap(b, 4, 1);
            moves[j++] = Board(b).getHash();
            swap(b, 4, 1);
            swap(b, 4, 3);
            moves[j++] = Board(b).getHash();
            swap(b, 4, 3);
            swap(b, 4, 5);
            moves[j++] = Board(b).getHash();
            swap(b, 4, 5);
            swap(b, 4, 7);
            moves[j++] = Board(b).getHash();
            swap(b, 4, 7);
            break;
        case 5:
            swap(b, 5, 2);
            moves[j++] = Board(b).getHash();
            swap(b, 5, 2);
            swap(b, 5, 4);
            moves[j++] = Board(b).getHash();
            swap(b, 5, 4);
            swap(b, 5, 8);
            moves[j++] = Board(b).getHash();
            swap(b, 5, 8);
            break;
        case 6:
            swap(b, 6, 3);
            moves[j++] = Board(b).getHash();
            swap(b, 6, 3);
            swap(b, 6, 7);
            moves[j++] = Board(b).getHash();
            swap(b, 6, 7);
            break;
        case 7:
            swap(b, 7, 4);
            moves[j++] = Board(b).getHash();
            swap(b, 7, 4);
            swap(b, 7, 6);
            moves[j++] = Board(b).getHash();
            swap(b, 7, 6);
            swap(b, 7, 8);
            moves[j++] = Board(b).getHash();
            swap(b, 7, 8);
            break;
        case 8:
            swap(b, 8, 5);
            moves[j++] = Board(b).getHash();
            swap(b, 8, 5);
            swap(b, 8, 7);
            moves[j++] = Board(b).getHash();
            swap(b, 8, 7);
            break;
    }

    return;
}

int Board::getDistance(int b)
{
    Board b2(b);
    int *b2array = b2.getBoard();
    int distance = 0;

    // loop through each cell in board
    // and then find where it is in b
    for (int i=0; i<9; i++)
    {
        int j;
        // find in b2array
        for (j=0; j<9; j++)
            if (board[i] == b2array[j]) break;

        // update distance
        distance += abs(getCol(i) - getCol(j)) + abs(getRow(i) -getRow(j));
    }

    return distance;
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



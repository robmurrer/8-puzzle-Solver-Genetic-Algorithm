#include <vector>
#include <cstring>
#ifndef BOARD_H 
#define BOARD_H

using namespace std;


class Board
{
    private:
        int board[9];
        int _board[9]; 
        int hash;
        int manhattan;
        int moves[4];

        void calcHash();
        void calcManhattan();
        void calcMoves();

    public:
        Board(const char *conf);
        Board(const int arrayboard[9]);
        Board(const int hash); 

        int getHash() { calcHash(); return hash; }
        int getManhattan() { calcManhattan(); return manhattan; }
        int * getBoard() { for(int i=0; i<9; i++) _board[i] = board[i]; return _board; } 
        int * getMoves() { calcMoves(); return moves; }
        void printPretty();
        void printConf();
};

namespace BoardSpace
{
    const int goalBoard[9] = { 8, 0, 1, 2, 3, 4, 5, 6, 7 };
    const int goalBoardHash = 876543210;

    int getCol(int);
    int getRow(int);
    void swap(int*, int, int);
}

#endif

#include <stdlib.h>
#include <stdio.h>
#include "solution.h"
#include "board.h"

Solution::Solution(int b)
{
    map.insert(make_pair(b, 0));
    list.push_front(b);
}

void Solution::mutate()
{
    // guard against removing original
    if (list.size() <= 1)
        return;

    // get current position
    Board b(list.back());

    //remove from solution
    list.pop_back();
    map.erase(b.getHash());

    //grow
    grow();

}
void Solution::grow()
{
    Board b(list.back());
    int *moves = b.getMoves();

    // calculate how many moves there are
    int i;
    for (i=0; i<4; i++)
        if (moves[i] == 0) break;

    // get random index
    int r = rand() % i;

    // add to map and list
    map.insert(make_pair(moves[r], list.size()));
    list.push_back(moves[r]);
}

void Solution::growBest()
{
    Board b(list.back());
    int *moves = b.getMoves();

    // calculate how many moves there are
    int i;
    for (i=0; i<4; i++)
        if (moves[i] == 0) break;


    // find move with best manhattan distance 
    int best_fitness = Board(moves[0]).getManhattan();
    int best_index = 0;

    for (int j=1; j<i; j++)
    {
        int tm = Board(moves[i]).getManhattan(); 
        if (tm > best_fitness)
        {
            best_index = 1;
            best_fitness = tm;
        }
    }

    // add to map and list
    map.insert(make_pair(moves[best_index], list.size()));
    list.push_back(moves[best_index]);
}

bool Solution::growNoCycle()
{
    Board b(list.back());
    int *moves = b.getMoves();

    // calculate how many moves there are
    int i;
    for (i=0; i<4; i++)
        if (moves[i] == 0) break;

    // goto random move that hasn't been explored before 
    for(int j=0; j<i; j++)
    {
        // get random index
        int r = rand() % i;

        if (map.count(moves[r]) == 0)
        {
            // add to map and list
            map.insert(make_pair(moves[r], list.size()));
            list.push_back(moves[r]);
            return true;
        }
    }

    // couldn't grow no all possibles have been visited
    // todo don't insert same one
    map.insert(make_pair(b.getHash(),list.size()));
    list.push_back(b.getHash());
    return false;

}

int Solution::getStatus() const
{
    return list.back();
}

double Solution::getFitness() const
{
    int manhattan = Board(getStatus()).getManhattan();
    int topleft = Board(getStatus()).getTopLeft();

    return 1 - (manhattan*.01) - (topleft*.1);
}

bool Solution::operator<(const Solution& rhs) const
{
    if ((getFitness() - rhs.getFitness()) <= 0) return false;
    else return true;
}

bool Solution::solved()
{
    if (getStatus() == BoardSpace::goalBoardHash) return true;
    else return false;
}

void Solution::print()
{
    printf("Initial Position: \n");
    Board(list[0]).printPretty();

    for(int i=1; i<list.size(); i++)
    {
        printf("\nGeneration %d:\n", i);
        Board(list[i]).printPretty();
    }
}

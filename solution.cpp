#include <stdlib.h>
#include "solution.h"

Solution::Solution(int b)
{
    map.insert(make_pair(b, 0));
    list.push_front(b);
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

double Solution::getFitness() const
{
    int manhattan = Board(getStatus()).getManhattan();

    return 1 - manhattan * .01;
}

bool Solution::operator<(const Solution& rhs) const
{
    if ((getFitness() - rhs.getFitness()) >= 0) return false;
    else return true;
}

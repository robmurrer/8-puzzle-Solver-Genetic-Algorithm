#include <stdlib.h>
#include <stdio.h>
#include "solution.h"
#include "board.h"
#include "dbh.h"

#define CROSSOVER_LOGGING false;

Solution::Solution(int b)
{
    map.insert(make_pair(b, 0));
    list.push_front(b);
}

void Solution::truncate()
{
    int size = list.size();
    // guard against removing original
    // and only truncate if larger than 31
    if (size <= 1 || size > 31) return;

    int number_to_cut = rand() % size;

    for(int i=0; i<number_to_cut; i++)
    {
        // get current position
        Board b(list.back());

        //remove from solution
        list.pop_back();
        map.erase(b.getHash());
    }
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
    growNoCycle();

}

// this will cause cycles, only call if you know what you are doing
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


void Solution::growBestNoCycle()
{
    Board b(list.back());
    int *moves = b.getMoves();

    if (b.getHash() == 0)
    {
        debug("This should never happen");
    }

    // calculate how many moves there are
    int i;
    for (i=0; i<4; i++)
        if (moves[i] == 0) break;

    // calculate how many moves haven't been made
    int legit_moves = -1;
    int nmoves[4];
    for (int j=0; j<i; j++)
    {
        if (map.count(moves[j]) == 0)
        {
            nmoves[++legit_moves] = moves[j];
        }

    }
    if (legit_moves == -1)
    {
        // do something like move random?
        mutate();
        //grow();
    }
    else
    {
        double best_fitness = Board(nmoves[0]).getFitness();
        int best_index = 0;

        for (int j=1; j<legit_moves+1; j++)
        {
            double tm = Board(nmoves[j]).getFitness(); 
            if (tm > best_fitness)
            {
                best_index = 1;
                best_fitness = tm;
            }
        }

        // add to map and list
        map.insert(make_pair(nmoves[best_index], list.size()));
        list.push_back(nmoves[best_index]);
    }


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

    return 1 - (manhattan*.01) - (topleft*.2);
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
        printf("\nMove %d:\n", i);
        Board(list[i]).printPretty();
    }
}

bool Solution::checkCycle()
{
    for(multimap<int,int>::iterator i=map.begin(); i != map.end(); ++i)
    {
        //printf("%d:%d\n", (*i).first, (*i).second);
        if (map.count((*i).first) > 1)
            return true;

    }
    return false;
}


// there is a serious bug in this do not use
// run under valgrind and see in illegal erasure
void Solution::crossover(Solution& strong)
{
    //static FILE *log = fopen("log/crossover.txt", "w");
    //static int log_counter = 1;

    //printf("Crossing over %d with strong mate: %d\n", this->getStatus(), strong.getStatus());
    
    // can always insert at start so keep that is worst point
    int left = 0;
    int right = 0; 
    for (int i=strong.list.size()-1; i>=0; i--)
    {
        if (map.count(strong.list[i]))
        {
            multimap<int,int>::iterator weak = map.find(strong.list[i]);
            //printf("found possible crossover state: %d at weak: %d, strong: %d\n",
                    //strong.list[i], weak->second, i);

            if (weak->second > left)
            {
                left = weak->second;
                right = i;
            }

        }
    }

    //printf("Crossing over at weak: %d and strong %d\n", left, right);
    //fprintf(log, "%d\t%d\t%d\n", log_counter++, left+1, right+1);

    // remove everything to the right of left in weak
    int weak_size = list.size();
    for (int i=(left+1); i<weak_size; i++)
    {
        int weak_hash = list[list.size()-1];
        //printf("weak_hash: %d\n", weak_hash);
        list.pop_back();
        map.erase(weak_hash);
    }

    //printf("Weak map size: %d weak list size: %d\n", (int)map.size(), (int)list.size());

    //copy over strongs right side
    for (int i=(right+1); i<strong.list.size(); i++)
    {
        map.insert(make_pair(strong.list[i], i));
        list.push_back(strong.list[i]);
    }

    //printf("Weak map size: %d weak list size: %d\n", (int)map.size(), (int)list.size());


    return;
}


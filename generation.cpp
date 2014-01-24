#include <stdio.h>
#include <stdlib.h>
#include "generation.h"
#include <map>

Generation::Generation(int _id, int _size, int _boardStart)
{
    id = _id;
    size = _size; 
    solutions.reserve(size);
    origin = Board(_boardStart).getHash(); 

    vector<Solution>::iterator it = solutions.begin(); 

    for (int i=0; i<size; i++)
        it = solutions.insert(it, Solution(_boardStart));
}

Generation::Generation(Generation& prev, int _unchecked_growth,
        double max_duplicates, double population_decrement)
{
    size = prev.getSize() - (int) (prev.getSize()*population_decrement);
    printf("size of generation: %d, population dec: %f\n", size, population_decrement);
    solutions.reserve(size);
    id = prev.getId() + 1;
    origin = prev.origin;
    unchecked_growth = _unchecked_growth;

    // used to keep track of number of board confs
    multimap<int,int> currentConf;

    // limit the number of solutions with current status
    // by keeping tracking reseting to origin if exceed max
    vector<Solution>::iterator it = solutions.begin(); 
    for (int i=0; i<size; i++)
    {
        Solution possible = prev.getFittest(i);
        
        //insert individual multiple times
        for (int j=0; j<(int)(size*max_duplicates); j++)
        {
            if (currentConf.count(possible.getStatus()) < (int)(size*max_duplicates)) 
            {
                it = solutions.insert(it, possible);
                currentConf.insert(make_pair(possible.getStatus(), 1));
            }
            else
            {
                //printf("individual exceeded limit: %d\n", possible.getStatus());
                break;
            }
        }

        // get out if we've already added the top performers
        if (solutions.size() == size)
        {
            //printf("enough individuals have been found\n");
            break;
        }

        if (i == solutions.size()-1)
        {
            //printf("enough individuals couldn't be found, inserting original\n");
            for (; i<size; i++)
                it = solutions.insert(it, Solution(origin));

            break;
        }
        
    }
}

void Generation::print()
{
    printf("Generation: %d\n", id);
    sort(solutions.begin(), solutions.end());
    for (int i=0; i<size; i++)
    {
        Board(solutions[i].getStatus()).printConf();
        printf(" %f\n", solutions[i].getFitness());
    }
}

void Generation::age()
{
    for (int i=0; i<size; i++)
    {
        if (solutions[i].list.size() <= unchecked_growth)
        {
            solutions[i].growNoCycle();
        }
        else 
        {
            int r = rand() % 4;
            switch(r)
            {
                case 0:
                    solutions[i].growBest();
                    break;
                case 1:
                    solutions[i].growNoCycle();
                    break;
                case 2:
                    solutions[i].grow();
                    break;
                case 3:
                    solutions[i].mutate();
                    break;
            }
        }

    }
}

bool Generation::cycle()
{

    // age population
    age();

    // sort decending and print population
    print();
    
    // if highest fitness is solved then return true
    return solutions[0].solved();
}


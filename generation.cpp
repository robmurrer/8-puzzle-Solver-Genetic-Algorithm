#include <stdio.h>
#include <stdlib.h>
#include "generation.h"
#include <map>

Generation::Generation(int _id, int size, int _boardStart)
{
    id = _id;
    solutions.reserve(size);

    vector<Solution>::iterator it = solutions.begin(); 

    for (int i=0; i<size; i++)
        it = solutions.insert(it, Solution(_boardStart));
}

void Generation::grow()
{
    for (int i=0; i<solutions.size(); i++)
        solutions[i].grow();
}

void Generation::growBest()
{
    for (int i=0; i<solutions.size(); i++)
        solutions[i].growBestNoCycle();
}

Solution Generation::getBest()
{
    return solutions[0];
}
    
bool Generation::checkSolved()
{
    return solutions[0].solved();
}

void Generation::prepareSort()
{
    sort(solutions.begin(), solutions.end());
}
void Generation::printVerbose()
{
    printf("Generation: %d\n", id);
    prepareSort();
    for (int i=0; i<solutions.size(); i++)
    {
        Board(solutions[i].getStatus()).printConf();
        printf(" %f\n", solutions[i].getFitness());
    }
}




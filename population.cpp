#include <stdio.h>
#include <stdlib.h>
#include "population.h"
#include <map>

Population::Population(int _id, int size, int _boardStart)
{
    id = _id;
    solutions.reserve(size);

    vector<Solution>::iterator it = solutions.begin(); 

    for (int i=0; i<size; i++)
        it = solutions.insert(it, Solution(_boardStart));
}

void Population::grow()
{
    for (int i=0; i<solutions.size(); i++)
        //solutions[i].grow();
        solutions[i].growNoCycle();
}

void Population::growBest()
{
    for (int i=0; i<solutions.size(); i++)
        solutions[i].growBestNoCycle();
}

Solution Population::getBest()
{
    return solutions[0];
}
    
bool Population::checkSolved()
{
    return solutions[0].solved();
}

void Population::prepareSort()
{
    sort(solutions.begin(), solutions.end());
}
void Population::printVerbose()
{
    printf("Population: %d\n", id);
    for (int i=0; i<solutions.size(); i++)
    {
        Board(solutions[i].getStatus()).printConf();
        printf(" %f\n", solutions[i].getFitness());
    }
}

void Population::printSummary()
{
    printf("Population: %d\n", id);
    for (int i=0; i<(int)(.05*solutions.size()); i++)
    {
        Board(solutions[i].getStatus()).printConf();
        printf(" %f\n", solutions[i].getFitness());
    }
}

Solution crossover(Solution& strong, Solution& weak)
{
    //printf("crossing over %d with %d\n", strong.getStatus(), weak.getStatus());
    weak.mutate();
    return weak; 
}


void Population::selection(int elites)
{
   for (int i=elites; i<solutions.size(); i++)
   {
       solutions[i] = crossover(solutions[i%elites], solutions[i]);
   }
}

void Population::checkCycles()
{
    for (int i=0; i<solutions.size(); i++)
        if (solutions[i].checkCycle())
            printf("Cycle Found\n");
}

void Population::age()
{ 
    id++;
}


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
        solutions[i].growNoCycle();
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
    for (int i=0; i<solutions.size(); i++)
    {
        Board(solutions[i].getStatus()).printConf();
        printf(" %f\n", solutions[i].getFitness());
    }
}

void Generation::printSummary()
{
    printf("Generation: %d\n", id);
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


void Generation::selection(int elites)
{
   for (int i=elites; i<solutions.size(); i++)
   {
       solutions[i] = crossover(solutions[i%elites], solutions[i]);
   }
}

void Generation::checkCycles()
{
    for (int i=0; i<solutions.size(); i++)
        solutions[i].checkCycle();
}

void Generation::age()
{ 
    id++;
}


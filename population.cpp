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

void Population::growBest(int pm)
{
    for (int i=0; i<solutions.size(); i++)
    {
        // only mutate with a certain probability
        int r = rand() % pm;
        if (r==0)
            solutions[i].growBestNoCycle();
    }
}

Solution Population::getBest()
{
    return solutions[0];
}
    
bool Population::checkSolved()
{
    return solutions[0].solved();
}

void Population::sort()
{
    std::sort(solutions.begin(), solutions.end());
}
void Population::printVerbose()
{
    printf("Generation: %d\n", id);
    for (int i=0; i<solutions.size(); i++)
    {
        Board(solutions[i].getStatus()).printConf();
        printf(" %f\n", solutions[i].getFitness());
    }
}

void Population::printSummary()
{
    printf("Generation: %d\n", id);
    for (int i=0; i<(int)(.05*solutions.size()); i++)
    {
        Board(solutions[i].getStatus()).printConf();
        printf(" %f\n", solutions[i].getFitness());
    }
}


void Population::selection(int elites, int cm)
{
   for (int i=elites; i<solutions.size(); i++)
   {
        // only crossover with certain probability
        int r = rand() % cm;
        if (r==0)
            solutions[i].crossover(solutions[i%elites]);
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

void Population::mutate(int mrate)
{
    for (int i=0; i<solutions.size(); i++)
    {
        int r = rand() % mrate;
        if (r == 0)
        {
            r = rand() % 4;
            if (r == 0) solutions[i].growBestNoCycle();
            if (r == 1) solutions[i].growNoCycle();
            if (r == 2) solutions[i].mutate();
            if (r == 3) solutions[i].truncate();
        }
    }
}


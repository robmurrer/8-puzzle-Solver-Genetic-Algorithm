#include <stdio.h>
#include "generation.h"

Generation::Generation(int _id, int _size, int _boardStart)
{
    id = _id;
    size = _size; 
    solutions.reserve(size);

    vector<Solution>::iterator it = solutions.begin(); 

    for (int i=0; i<size; i++)
        it = solutions.insert(it, Solution(_boardStart));
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
        solutions[i].grow();
}

bool Generation::cycle()
{
    // advance generation
    id++;

    // age population
    age();

    // sort decending and print population
    print();
    
    // if highest fitness is solved then return true
    return solutions[0].solved();
}


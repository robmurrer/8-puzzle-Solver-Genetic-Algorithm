#include <stdlib.h>
#include "world.h"
#include "generation.h"
#include "board.h"
#include "dbh.h"

#define SOLUTION_INIT_SIZE 30 
#define RAND_SEED 1982
#define POPULATION_SIZE 100
#define NUMBER_GENS 100 
#define BOARD  32871456 

World::World(int _origin, int _pop_size, int _num_gens, double _mutation, double _crossover) 
    : population(1, POPULATION_SIZE, BOARD)
    //: population(1, _pop_size, _origin)
{
    // init member variables
    //pop_size = _pop_size;
    //num_gens = _num_gens;
    pop_size = POPULATION_SIZE; 
    num_gens = NUMBER_GENS;
    //origin = _origin;
    origin = BOARD;
    mutation = _mutation;
    crossover = _crossover;
    solved = false;

    // seed random number gen
    srand(RAND_SEED);
    printf("\nWorld Created\n");
    printf("Board: ");
    Board(origin).printConf();
    printf(", Population: %d, Generations: %d, Pc: %f, Pm: %f\n", pop_size, num_gens, crossover, mutation);

    //initialize population
    for (int i=0; i<SOLUTION_INIT_SIZE; i++)
    {
        population.grow();
        population.prepareSort();
        if (population.checkSolved())
        {
            printf("Got really lucky and grew into solution on first generation.\n");
            population.solutions[0].print();
            solved = true;
            break;
        }
    }



            
}

void World::start()
{
    for(int i=0; i<num_gens; i++)
    {
        if (population.cycle()) break;
    }

    population.solutions[0].print();
}

#include <stdlib.h>
#include <time.h>
#include "world.h"
#include "generation.h"
#include "board.h"
#include "dbh.h"

#define SOLUTION_INIT_SIZE 30
//#define RAND_SEED 1982
#define RAND_SEED time(0) 
#define POPULATION_SIZE 100
#define NUMBER_GENS 150 
//#define BOARD  32871456 
#define BOARD 876543210 
#define ELITES 0.1
#define MUTATION 1.0
#define CROSSOVER 1.0

World::World(int _origin, int _pop_size, int _num_gens, double _mutation, double _crossover) 
    : population(1, _pop_size, _origin)
{
    // init member variables
    pop_size = _pop_size;
    num_gens = _num_gens;
    origin = _origin;
    elites = (int) (ELITES * pop_size);
    mutation = _mutation;
    crossover = _crossover;
    solved = false;

    // seed random number gen
    srand(RAND_SEED);
    printf("\nWorld Created\n");
    printf("Board: ");
    Board(origin).printConf();
    printf(", Population: %d, Generations: %d, Pc: %f, Pm: %f\n", pop_size, num_gens, crossover, mutation);

    seedPopulation();
}


// A testing constructor that pulls in defines rather than cmdline args 
World::World() : population(0, POPULATION_SIZE, BOARD)
{
    pop_size = POPULATION_SIZE; 
    num_gens = NUMBER_GENS;
    origin = BOARD;
    elites = (int) (ELITES * pop_size);
    mutation = MUTATION;
    crossover = CROSSOVER;
    solved = false;

    // seed random number gen
    srand(RAND_SEED);
    printf("\nWorld Created\n");
    printf("Board: ");
    Board(origin).printConf();
    printf(", Population: %d, Generations: %d, Pc: %f, Pm: %f\n", pop_size, num_gens, crossover, mutation);

    seedPopulation();

            
}

void World::seedPopulation()
{
    //initialize population
    for (int i=0; i<SOLUTION_INIT_SIZE; i++)
    {
        population.grow();
        population.prepareSort();
        if (population.checkSolved())
        {
            printf("Got really lucky and grew into solution on initial population creation.\n");
            population.getBest().print();
            solved = true;
            break;
        }
    }

}

void World::start()
{
    for(int i=0; i<num_gens; i++)
    {
        population.age();
        population.growBest();
        population.prepareSort();
        population.selection(elites);
        //population.printVerbose();
        population.printSummary();
        // if solution has been found break;
        if (population.checkSolved()) break;
    }

    population.getBest().print();
}

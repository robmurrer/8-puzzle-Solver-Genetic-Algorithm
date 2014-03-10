#include <stdlib.h>
#include <time.h>
#include "world.h"
#include "population.h"
#include "board.h"
#include "dbh.h"

#define SOLUTION_INIT_SIZE 10 
//#define RAND_SEED 2010
//#define RAND_SEED 1982
#define RAND_SEED time(0) 
#define POPULATION_SIZE 500 
#define NUMBER_GENS 10 
#define ELITES 0.1
#define MUTATION 1.0
#define CROSSOVER 0.15

World::World(int _origin, int _pop_size, int _num_gens, double _mutation, double _crossover) 
    : population(1, _pop_size, _origin)
{
    // init member variables
    pop_size = _pop_size;
    num_gens = _num_gens;
    origin = _origin;
    elites = (int) (ELITES * pop_size);
    mutation = (int)1/_mutation;
    crossover = (int)1/_crossover;
    solved = false;

    // seed random number gen
    srand(RAND_SEED);
    printf("\nWorld Created\n");
    printf("Board: ");
    Board(origin).printConf();
    printf(", Population: %d, Generations: %d, Pc: %f, Pm: %f\n", pop_size, num_gens, _crossover, _mutation);

    seedPopulation();
}


// A testing constructor that pulls in defines rather than cmdline args 
World::World(int board, bool _enhanced) : population(0, POPULATION_SIZE, board)
{
    pop_size = POPULATION_SIZE; 
    num_gens = NUMBER_GENS;
    origin = board;
    elites = (int) (ELITES * pop_size);
    mutation = (int)1/MUTATION;
    crossover = (int)1/CROSSOVER;
    solved = false;
    enhanced = _enhanced;

    // seed random number gen
    srand(RAND_SEED);
    printf("\nWorld Created\n");
    printf("Board: ");
    Board(origin).printConf();
    printf(", Population: %d, Generations: %d, Pc: %f, Pm: %f\n", pop_size, num_gens, CROSSOVER, MUTATION);
    printf("%s Mode\n", (enhanced ? "Enhanced" : "Baseline"));

    seedPopulation();

            
}

void World::seedPopulation()
{
    //initialize population
    for (int i=0; i<SOLUTION_INIT_SIZE; i++)
    {
        population.mutate(1.0);
        population.sort();
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
    FILE *log = fopen("log/data.txt", "w");
    
    int i;
    for(i=0; i<num_gens; i++)
    {
        population.calcDiversity();
        fprintf(log, "%d\t%f\t%f\t%f\n", 
                i, population.getMeanDistance(), population.getAvgFitness(), 
                population.getBest().getFitness());
        population.mutate(mutation);
        population.sort();
        population.selection(elites,crossover);
        //population.printVerbose();
        //population.printSummary();
        printf(".");

        // if solution has been found break;
        if (population.checkSolved()) 
        {
            solved = true;
            break;
        }
        population.age();
    }

    printf("\n");

    population.getBest().print();
    if (solved)
    {
        printf("Solution Found in %d generations\n", i+1);
        fprintf(log, "%d\t%f\t%f\t%f\n", 
            i, population.getMeanDistance(), population.getAvgFitness(), 
            population.getBest().getFitness());
    }
    else printf("No solution Found\n");

    fclose(log);
    log = fopen("log/title.txt", "w");
    fprintf(log, 
            "%s - pop: %d - gen: %d - mutation: %.3f - crossover: %.3f\
            \nelites: %d - init size: %d - board: %d - %s - %d moves", 
            (enhanced ? "Enhanced" : "Baseline"), pop_size, num_gens, (double) 1/mutation, 
            (double) 1/crossover, elites, SOLUTION_INIT_SIZE, origin, 
            (solved ? "SOLVED" : "NOT SOLVED"),
            population.getBest().getSize()); 
    fclose(log);
    log = fopen("log/file.txt", "w");
    fprintf(log, 
            "%s-%d-pop:%d-gen:%d-mut:%.3f-xover:%.3f-elites:%d-isize:%d-%s-%d-moves", 
            (enhanced ? "enh" : "bl"), origin, pop_size, num_gens, 
            (double) 1/mutation, (double) 1/crossover, 
            elites, SOLUTION_INIT_SIZE, (solved ? "SOLVED" : "NOT-SOLVED"),
            population.getBest().getSize()); 
    fclose(log);
}

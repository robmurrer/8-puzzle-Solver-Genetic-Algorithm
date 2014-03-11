#include <stdlib.h>
#include <time.h>
#include "world.h"
#include "population.h"
#include "board.h"
#include "dbh.h"

#define LOGGING true

// use same seed for comparing bl and enh
#define RAND_SEED 2010
//#define RAND_SEED 1982
//#define RAND_SEED time(0) 

// for both enhanced and bl use same pop/gen for fairness
#define POPULATION_SIZE 500 
#define NUMBER_GENS 500 

// baseline
#define BL_SOLUTION_INIT_SIZE 1 
#define BL_ELITES 0.3
#define BL_MUTATION 1.0
#define BL_CROSSOVER 0.1

// enhanced
#define EN_SOLUTION_INIT_SIZE 30 
#define EN_ELITES 0.3
#define EN_MUTATION 1.0
#define EN_CROSSOVER 0.1

World::World(int board, bool _enhanced) : population(0, POPULATION_SIZE, board)
{
    pop_size = POPULATION_SIZE; 
    num_gens = NUMBER_GENS;
    origin = board;

    elites = (int) ((_enhanced ? EN_ELITES : BL_ELITES)* pop_size);
    mutation = (int)1/(_enhanced ? EN_MUTATION : BL_MUTATION);
    crossover = (int)1/(_enhanced ? EN_CROSSOVER : BL_CROSSOVER);
    solved = false;
    enhanced = _enhanced;

    // seed random number gen
    srand(RAND_SEED);
    printf("\nWorld Created\n");
    printf("Board: ");
    Board(origin).printConf();
    printf(", Population: %d, Generations: %d, Pc: %f, Pm: %f\n", 
            pop_size, num_gens, (_enhanced ? EN_CROSSOVER : BL_CROSSOVER), 
            (_enhanced ? EN_MUTATION : BL_MUTATION));
    printf("%s Mode\n", (enhanced ? "Enhanced" : "Baseline"));

    seedPopulation();

            
}

void World::seedPopulation()
{
    //initialize population
    for (int i=0; i<(enhanced ? EN_SOLUTION_INIT_SIZE : BL_SOLUTION_INIT_SIZE); i++)
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
        fprintf(log, "%d\t%f\t%f\t%f\t%f\n", 
                i, population.getMeanDistance(), population.getAvgFitness(), 
                population.getBest().getFitness(), 
                (double)population.getUniqueIndividuals()/pop_size);
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
            "%s - pop: %d - gen: %d - mutat: %.3f - xover: %.3f - seed: %ld\
            \nelites: %d - isize: %d - board: %d - %s - %d moves", 
            (enhanced ? "Enhanced" : "Baseline"), pop_size, num_gens, (double) 1/mutation, 
            (double) 1/crossover, (long)RAND_SEED, elites, 
            (enhanced ? EN_SOLUTION_INIT_SIZE : BL_SOLUTION_INIT_SIZE), origin, 
            (solved ? "SOLVED" : "NOT SOLVED"),
            population.getBest().getSize()); 
    fclose(log);
    log = fopen("log/file.txt", "w");
    fprintf(log, 
            "%s-%d-pop_%d-gen_%d-mut_%.3f-xover_%.3f-elites_%d-isize_%d-seed_%ld-%s-%d-moves", 
            (enhanced ? "enh" : "bl"), origin, pop_size, num_gens, 
            (double) 1/mutation, (double) 1/crossover, 
            elites, (enhanced ? EN_SOLUTION_INIT_SIZE : BL_SOLUTION_INIT_SIZE), 
            (long)RAND_SEED, (solved ? "SOLVED" : "NOT-SOLVED"),
            population.getBest().getSize()); 
    fclose(log);
}

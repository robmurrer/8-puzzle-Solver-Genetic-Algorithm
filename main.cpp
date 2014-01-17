#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "solution.h"

using namespace std;

int main(int argc, char **argv)
{
    // read in command line arguments
    char *argBuffer;
    char *boardStart;
    argc--; argv++;
    boardStart = *argv;


    // read in optional command line args
    int population, generations;
    double pc, pm;
    if (argc != 1)
    {
        argc--; argv++;
        argBuffer = *argv;
        population = atoi(argBuffer);
        argc--; argv++;
        argBuffer = *argv;
        generations = atoi(argBuffer);
        argc--; argv++;
        argBuffer = *argv;
        pc = atof(argBuffer);
        argc--; argv++;
        argBuffer = *argv;
        pm = atof(argBuffer);

    }

    // provide defaults if none were provided
    else
    {
        population = 20;
        generations = 100;
        pc = 0.0;
        pm = 1;
    }

    printf("Board: %s, Population: %d, Generations: %d, Pc: %f, Pm: %f\n", 
            boardStart, population, generations, pc, pm);
    srand(time(0));

    Solution sol(Board(boardStart).getHash());

    Solution sol2 = sol;

    sol2.grow();

    printf("Solution 1: %d fitness: %f\n", sol.getStatus(), sol.getFitness());
    printf("Solution 2: %d fitness: %f\n", sol2.getStatus(), sol2.getFitness());

    if (sol < sol2) printf("Solution1 < Solution2\n");
    else printf("Solution1 > Solution2\n");


    return 0;
}


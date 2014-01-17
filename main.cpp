#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "solution.h"
#include "generation.h"

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
        population = 10;
        generations = 2;
        pc = 0.0;
        pm = 1;
    }

    printf("Board: %s, Population: %d, Generations: %d, Pc: %f, Pm: %f\n", 
            boardStart, population, generations, pc, pm);
    srand(time(0));

    Generation gen(0, population, Board(boardStart).getHash()); 
    
    for(int i=0; i<generations; i++)
    {
        // age population, sort, print, check if solved
        if (gen.cycle() == true)
            break;
    }

    return 0;
}


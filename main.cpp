#include <stdlib.h>
#include "board.h"
#include "world.h"
#include "test.h"


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

        World world(Board(boardStart).getHash(), population, generations, pm, pc);
        if (!world.solved)
            world.start();
    }

    // provide defaults if none were provided
    else
    {
        World world;
        if (!world.solved)
            world.start();
    }
   



    return 0;
}


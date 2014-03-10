#include <stdlib.h>
#include "board.h"
#include "world.h"
#include "test.h"


int main(int argc, char **argv)
{
    // no board just run tests
    if (argc == 1)
    {
        run_tests();
        return 0;
    }

    // read in command line arguments
    char *argBuffer;
    char *boardStart;
    argc--; argv++;
    boardStart = *argv;

    // read in optional command line args
    int population, generations;
    double pc, pm;



    // board only
    if (argc == 1)
    {
        World world(Board(boardStart).getHash());
        if (!world.solved)
            world.start();
    }

    // board and args
    else
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

   



    return 0;
}


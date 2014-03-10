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
    char *boardStart;
    argc--; argv++;
    boardStart = *argv;


    // Regular GA
    if (argc == 1)
    {
        World world(Board(boardStart).getHash(), false);
        if (!world.solved)
            world.start();
    }

    // Enhanced GA 
    else
    {
        World world(Board(boardStart).getHash(), true);
        if (!world.solved)
            world.start();
    }

   

    return 0;
}


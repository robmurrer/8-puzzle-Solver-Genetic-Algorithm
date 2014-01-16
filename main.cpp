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
    argc--; argv++;
    argBuffer = *argv;
    int population = atoi(argBuffer);
    argc--; argv++;
    argBuffer = *argv;
    int generations = atoi(argBuffer);
    argc--; argv++;
    argBuffer = *argv;
    double pc = atof(argBuffer);
    argc--; argv++;
    argBuffer = *argv;
    double pm = atof(argBuffer);


    printf("Board: %s, Population: %d, Generations: %d, Pc: %f, Pm: %f\n", 
            boardStart, population, generations, pc, pm);

    srand(time(0));

    Solution sol(Board(boardStart).getHash());

    printf("Current status: %d\n", sol.getStatus());
    printf("Growing...\n");
    sol.grow();
    printf("Current status: %d\n", sol.getStatus());
    printf("Growing...\n");
    sol.grow();
    printf("Current status: %d\n", sol.getStatus());
    printf("Growing...\n");
    sol.grow();
    printf("Current status: %d\n", sol.getStatus());
    printf("Growing...\n");
    sol.grow();
    printf("Current status: %d\n", sol.getStatus());

    for(int i=0; i<sol.list.size(); i++)
        printf("list[%d] = %d, map[%d] = %d\n", 
                i, sol.list[i], sol.list[i], sol.map.find(sol.list[i])->second);

    return 0;
}


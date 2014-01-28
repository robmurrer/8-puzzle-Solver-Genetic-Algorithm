#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "solution.h"
#include "dbh.h"

bool test_miss_placed()
{
    check_debug((Board(123456780).getMisPlaced() == 0), "Perfect board should have 0 misplaced");

    check_debug((Board(123456708).getMisPlaced() == 2), "should have misplaced of 2");
    return true;
error:
    return false;
}

bool test_crossover()
{


    int board = 87654321; 
    srand(0);

    Solution a(board);
    for (int i=0; i<10; i++)
    {
        a.growNoCycle();
    }

    Solution b(board);
    for (int i=0; i<10; i++)
    {
        b.growBestNoCycle();
    }

    printf("Solution A\n");
    //a.print();
    printf("Fitness: %f\n", a.getFitness());

    printf("Solution B\n");
    //b.print();
    printf("Fitness: %f\n", b.getFitness());

    a.crossover(b);
    //a.print();

    return true;
}

bool test_checkCycle()
{
    srand(0);
    Solution sol(123456780);
    sol.grow();
    sol.grow();
    sol.grow();
    check_debug(sol.checkCycle(), "Did not detect cycle");
    return true;
error:
    return false;

}

bool test_grow_best()
{

    check_debug(Board(123456780).getFitness() == 1.0, "Wrong Fitness, should be 1.0");
    return true;

error:
    return false;
}

bool test_test()
{
    printf("Testing Tests\n");
    return true;
}


bool (*tests[])() = 
{ 
    test_miss_placed,
    test_crossover,
    test_checkCycle,
    test_grow_best,
    test_test 
};
      

void run_tests()
{
    int i = 0;
    while(tests[i] != NULL)
        (*tests[i++])();
        
}

